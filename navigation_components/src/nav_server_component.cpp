#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2/utils.h>
#include "navigation_components/action/navigate.hpp"
#include <thread>
#include <mutex>

using std::placeholders::_1;
using std::placeholders::_2;

class NavServer : public rclcpp::Node
{
public:
  using Navigate = navigation_components::action::Navigate;
  using GoalHandle = rclcpp_action::ServerGoalHandle<Navigate>;

  NavServer(const rclcpp::NodeOptions & options) : Node("nav_server", options)
  {
    kp_lin_ = this->declare_parameter("kp_linear", 0.5);
    kp_ang_ = this->declare_parameter("kp_angular", 0.5);
    dist_thresh_ = this->declare_parameter("distance_threshold", 0.1);

    cmd_pub_ = create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    
    odom_sub_ = create_subscription<nav_msgs::msg::Odometry>(
      "odom", 10, [this](const nav_msgs::msg::Odometry::SharedPtr msg) {
        current_x_ = msg->pose.pose.position.x;
        current_y_ = msg->pose.pose.position.y;
        current_yaw_ = tf2::getYaw(msg->pose.pose.orientation);
        odom_received_ = true;
      });

    action_server_ = rclcpp_action::create_server<Navigate>(
      this, "navigate",
      std::bind(&NavServer::handle_goal, this, _1, _2),
      std::bind(&NavServer::handle_cancel, this, _1),
      std::bind(&NavServer::handle_accepted, this, _1)
    );
  }

private:
  double current_x_{0.0}, current_y_{0.0}, current_yaw_{0.0};
  bool odom_received_{false};
  float kp_lin_, kp_ang_, dist_thresh_;

  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub_;
  rclcpp_action::Server<Navigate>::SharedPtr action_server_;

  std::shared_ptr<GoalHandle> current_executing_goal_;
  std::mutex goal_mtx_;

  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID &, std::shared_ptr<const Navigate::Goal>)
  {
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandle>)
  {
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  void handle_accepted(const std::shared_ptr<GoalHandle> goal_handle)
  {
    std::thread{std::bind(&NavServer::execute, this, _1), goal_handle}.detach();
  }

  void execute(const std::shared_ptr<GoalHandle> goal_handle)
  {
    {
      std::lock_guard<std::mutex> lock(goal_mtx_);
      current_executing_goal_ = goal_handle;
    }

    auto goal = goal_handle->get_goal();
    auto feedback = std::make_shared<Navigate::Feedback>();
    auto result = std::make_shared<Navigate::Result>();
    rclcpp::Rate rate(10);

    while (rclcpp::ok()) {
      if (current_executing_goal_ != goal_handle) {
        return;
      }

      if (goal_handle->is_canceling()) {
        stop_robot();
        goal_handle->canceled(result);
        return;
      }

      if (!odom_received_) {
        rate.sleep();
        continue;
      }

      double dx = goal->x - current_x_;
      double dy = goal->y - current_y_;
      double dist = std::hypot(dx, dy);
      double target_yaw = std::atan2(dy, dx);
      double err_ang = target_yaw - current_yaw_;
      
      err_ang = std::atan2(std::sin(err_ang), std::cos(err_ang));

      feedback->distance_to_goal = dist;
      goal_handle->publish_feedback(feedback);
      geometry_msgs::msg::Twist cmd;

      if (dist < dist_thresh_) 
      {
        if (std::abs(err_ang) > 0.3) {
        cmd.linear.x = 0.0;
        cmd.angular.z = kp_ang_ * err_ang;
      }
        break;

      }

      
      if (std::abs(err_ang) > 0.3) {
        cmd.linear.x = 0.0;
        cmd.angular.z = kp_ang_ * err_ang;
      } else {
        cmd.linear.x = kp_lin_ * dist;
        cmd.angular.z = kp_ang_ * err_ang;
      }
      
      cmd_pub_->publish(cmd);

      rate.sleep();
    }

    if (current_executing_goal_ == goal_handle) {
      stop_robot();
      result->success = true;
      goal_handle->succeed(result);
    }
  }

  void stop_robot() {
    geometry_msgs::msg::Twist cmd;
    cmd_pub_->publish(cmd);
  }
};

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(NavServer)