#include <cmath> 
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>

#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2/utils.h>

#include "custom_interfaces/actions/navigate.hpp"

class NavServer : public rclcpp::Node
{
public:
  using Navigate = custom_interfaces::action::Navigate;
  using GoalHandle = rclcpp_action::ServerGoalHandle<Navigate>;

  NavServer(const rclcpp::NodeOptions & options)
  : Node("nav_server", options)
  {
    kp_lin_ = this->declare_parameter("kp_linear", 0.5);
    kp_ang_ = this->declare_parameter("kp_angular", 1.0);
    dist_thresh_ = this->declare_parameter("distance_threshold", 0.1);

    cmd_pub_ = create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);

    tf_buffer_ = std::make_unique<tf2_ros::Buffer>(get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    action_server_ = rclcpp_action::create_server<Navigate>(
      this, "navigate",
      std::bind(&NavServer::handle_goal, this, _1, _2),
      std::bind(&NavServer::handle_cancel, this, _1),
      std::bind(&NavServer::execute, this, _1)  
    );
  }

private:
  double kp_lin_, kp_ang_, dist_thresh_;

  rclcpp_action::Server<Navigate>::SharedPtr action_server_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub_;
  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  rclcpp_action::GoalResponse handle_goal(
    const rclcpp_action::GoalUUID &, std::shared_ptr<const Navigate::Goal>)
  {
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  rclcpp_action::CancelResponse handle_cancel(
    const std::shared_ptr<GoalHandle>)
  {
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  void execute(const std::shared_ptr<GoalHandle> goal_handle)
  {
    auto goal = goal_handle->get_goal();
    auto feedback = std::make_shared<Navigate::Feedback>();
    auto result = std::make_shared<Navigate::Result>();

    rclcpp::Rate rate(10);

    while (rclcpp::ok())
    {
      if (goal_handle->is_canceling()) {
        stop_robot();
        goal_handle->canceled(result);
        return;
      }

      geometry_msgs::msg::TransformStamped tf;
      try {
        tf = tf_buffer_->lookupTransform("odom", "base_link", tf2::TimePointZero);
      } catch (...) {
        rate.sleep();
        continue;
      }

      double current_x = tf.transform.translation.x;
      double current_y = tf.transform.translation.y;
      double yaw = tf2::getYaw(tf.transform.rotation);

      double dx = goal->x - current_x;
      double dy = goal->y - current_y;
      double dist = std::hypot(dx, dy);
      double target_yaw = std::atan2(dy, dx);
      double err_ang = target_yaw - yaw;

      err_ang = std::atan2(std::sin(err_ang), std::cos(err_ang));

      feedback->distance_to_goal = dist;
      goal_handle->publish_feedback(feedback);

      if (dist < dist_thresh_) break;

      geometry_msgs::msg::Twist cmd;
      cmd.linear.x  = kp_lin_ * dist;
      cmd.angular.z = kp_ang_ * err_ang;

      cmd_pub_->publish(cmd);
      rate.sleep();
    }

    stop_robot();
    result->success = true;
    goal_handle->succeed(result);
  }

  void stop_robot()
  {
    geometry_msgs::msg::Twist cmd;
    cmd_pub_->publish(cmd);
  }
};