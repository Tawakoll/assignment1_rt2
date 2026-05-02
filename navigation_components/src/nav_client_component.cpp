#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <std_msgs/msg/empty.hpp>
#include "navigation_components/action/navigate.hpp"
using std::placeholders::_1;
using std::placeholders::_2;

class NavClient : public rclcpp::Node
{
public:
  using Navigate = navigation_components::action::Navigate;
  using GoalHandle = rclcpp_action::ClientGoalHandle<Navigate>;

  NavClient(const rclcpp::NodeOptions & options)
  : Node("nav_client", options)
  {
    action_client_ = rclcpp_action::create_client<Navigate>(this, "navigate");

    target_sub_ = this->create_subscription<geometry_msgs::msg::Pose>(
      "/ui_target", 10, std::bind(&NavClient::target_callback, this, _1));
      
    cancel_sub_ = this->create_subscription<std_msgs::msg::Empty>(
      "/ui_cancel", 10, std::bind(&NavClient::cancel_callback, this, _1));
  }

private:
  rclcpp_action::Client<Navigate>::SharedPtr action_client_;
  rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr target_sub_;
  rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr cancel_sub_;
  
  GoalHandle::SharedPtr current_goal_handle_; 

  void target_callback(const geometry_msgs::msg::Pose::SharedPtr msg)
  {
    if (!action_client_->wait_for_action_server(std::chrono::seconds(2))) {
      RCLCPP_ERROR(this->get_logger(), "Action server not available!");
      return;
    }

    auto goal_msg = Navigate::Goal();
    goal_msg.x = msg->position.x;
    goal_msg.y = msg->position.y;
    goal_msg.theta = msg->orientation.z; 

    RCLCPP_INFO(this->get_logger(), "Sending goal: x=%.2f, y=%.2f theta=%.2f", goal_msg.x, goal_msg.y, goal_msg.theta);

    auto send_goal_options = rclcpp_action::Client<Navigate>::SendGoalOptions();
    send_goal_options.goal_response_callback = std::bind(&NavClient::goal_response_callback, this, _1);
    send_goal_options.feedback_callback = std::bind(&NavClient::feedback_callback, this, _1, _2);
    send_goal_options.result_callback = std::bind(&NavClient::result_callback, this, _1);

    action_client_->async_send_goal(goal_msg, send_goal_options);
  }

  void cancel_callback(const std_msgs::msg::Empty::SharedPtr)
  {
    if (current_goal_handle_) {
      RCLCPP_INFO(this->get_logger(), "Forwarding cancel request to action server...");
      action_client_->async_cancel_goal(current_goal_handle_);
    } else {
      RCLCPP_WARN(this->get_logger(), "No active goal to cancel.");
    }
  }

  void goal_response_callback(const GoalHandle::SharedPtr & goal_handle)
  {
    if (!goal_handle) {
      RCLCPP_ERROR(this->get_logger(), "Goal rejected by server.");
    } else {
      RCLCPP_INFO(this->get_logger(), "Goal accepted, executing...");
      current_goal_handle_ = goal_handle;
    }
  }

  void feedback_callback(GoalHandle::SharedPtr, const std::shared_ptr<const Navigate::Feedback> feedback)
  {
    RCLCPP_INFO(this->get_logger(), "Distance remaining: %.2f", feedback->distance_to_goal);
  }

  void result_callback(const GoalHandle::WrappedResult & result)
  {
    current_goal_handle_.reset();
    switch (result.code) {
      case rclcpp_action::ResultCode::SUCCEEDED:
        RCLCPP_INFO(this->get_logger(), "Target reached successfully!");
        break;
      case rclcpp_action::ResultCode::ABORTED:
        RCLCPP_ERROR(this->get_logger(), "Goal aborted.");
        break;
      case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_WARN(this->get_logger(), "Goal canceled.");
        break;
      default:
        RCLCPP_ERROR(this->get_logger(), "Unknown result code.");
        break;
    }
  }
};

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(NavClient)