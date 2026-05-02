// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from navigation_components:action/Navigate.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "navigation_components/action/navigate.hpp"


#ifndef NAVIGATION_COMPONENTS__ACTION__DETAIL__NAVIGATE__BUILDER_HPP_
#define NAVIGATION_COMPONENTS__ACTION__DETAIL__NAVIGATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "navigation_components/action/detail/navigate__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace navigation_components
{

namespace action
{

namespace builder
{

class Init_Navigate_Goal_theta
{
public:
  explicit Init_Navigate_Goal_theta(::navigation_components::action::Navigate_Goal & msg)
  : msg_(msg)
  {}
  ::navigation_components::action::Navigate_Goal theta(::navigation_components::action::Navigate_Goal::_theta_type arg)
  {
    msg_.theta = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_components::action::Navigate_Goal msg_;
};

class Init_Navigate_Goal_y
{
public:
  explicit Init_Navigate_Goal_y(::navigation_components::action::Navigate_Goal & msg)
  : msg_(msg)
  {}
  Init_Navigate_Goal_theta y(::navigation_components::action::Navigate_Goal::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Navigate_Goal_theta(msg_);
  }

private:
  ::navigation_components::action::Navigate_Goal msg_;
};

class Init_Navigate_Goal_x
{
public:
  Init_Navigate_Goal_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Navigate_Goal_y x(::navigation_components::action::Navigate_Goal::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Navigate_Goal_y(msg_);
  }

private:
  ::navigation_components::action::Navigate_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_components::action::Navigate_Goal>()
{
  return navigation_components::action::builder::Init_Navigate_Goal_x();
}

}  // namespace navigation_components


namespace navigation_components
{

namespace action
{

namespace builder
{

class Init_Navigate_Result_success
{
public:
  Init_Navigate_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::navigation_components::action::Navigate_Result success(::navigation_components::action::Navigate_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_components::action::Navigate_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_components::action::Navigate_Result>()
{
  return navigation_components::action::builder::Init_Navigate_Result_success();
}

}  // namespace navigation_components


namespace navigation_components
{

namespace action
{

namespace builder
{

class Init_Navigate_Feedback_distance_to_goal
{
public:
  Init_Navigate_Feedback_distance_to_goal()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::navigation_components::action::Navigate_Feedback distance_to_goal(::navigation_components::action::Navigate_Feedback::_distance_to_goal_type arg)
  {
    msg_.distance_to_goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_components::action::Navigate_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_components::action::Navigate_Feedback>()
{
  return navigation_components::action::builder::Init_Navigate_Feedback_distance_to_goal();
}

}  // namespace navigation_components


namespace navigation_components
{

namespace action
{

namespace builder
{

class Init_Navigate_SendGoal_Request_goal
{
public:
  explicit Init_Navigate_SendGoal_Request_goal(::navigation_components::action::Navigate_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::navigation_components::action::Navigate_SendGoal_Request goal(::navigation_components::action::Navigate_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_components::action::Navigate_SendGoal_Request msg_;
};

class Init_Navigate_SendGoal_Request_goal_id
{
public:
  Init_Navigate_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Navigate_SendGoal_Request_goal goal_id(::navigation_components::action::Navigate_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Navigate_SendGoal_Request_goal(msg_);
  }

private:
  ::navigation_components::action::Navigate_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_components::action::Navigate_SendGoal_Request>()
{
  return navigation_components::action::builder::Init_Navigate_SendGoal_Request_goal_id();
}

}  // namespace navigation_components


namespace navigation_components
{

namespace action
{

namespace builder
{

class Init_Navigate_SendGoal_Response_stamp
{
public:
  explicit Init_Navigate_SendGoal_Response_stamp(::navigation_components::action::Navigate_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::navigation_components::action::Navigate_SendGoal_Response stamp(::navigation_components::action::Navigate_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_components::action::Navigate_SendGoal_Response msg_;
};

class Init_Navigate_SendGoal_Response_accepted
{
public:
  Init_Navigate_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Navigate_SendGoal_Response_stamp accepted(::navigation_components::action::Navigate_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_Navigate_SendGoal_Response_stamp(msg_);
  }

private:
  ::navigation_components::action::Navigate_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_components::action::Navigate_SendGoal_Response>()
{
  return navigation_components::action::builder::Init_Navigate_SendGoal_Response_accepted();
}

}  // namespace navigation_components


namespace navigation_components
{

namespace action
{

namespace builder
{

class Init_Navigate_SendGoal_Event_response
{
public:
  explicit Init_Navigate_SendGoal_Event_response(::navigation_components::action::Navigate_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::navigation_components::action::Navigate_SendGoal_Event response(::navigation_components::action::Navigate_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_components::action::Navigate_SendGoal_Event msg_;
};

class Init_Navigate_SendGoal_Event_request
{
public:
  explicit Init_Navigate_SendGoal_Event_request(::navigation_components::action::Navigate_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_Navigate_SendGoal_Event_response request(::navigation_components::action::Navigate_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_Navigate_SendGoal_Event_response(msg_);
  }

private:
  ::navigation_components::action::Navigate_SendGoal_Event msg_;
};

class Init_Navigate_SendGoal_Event_info
{
public:
  Init_Navigate_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Navigate_SendGoal_Event_request info(::navigation_components::action::Navigate_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_Navigate_SendGoal_Event_request(msg_);
  }

private:
  ::navigation_components::action::Navigate_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_components::action::Navigate_SendGoal_Event>()
{
  return navigation_components::action::builder::Init_Navigate_SendGoal_Event_info();
}

}  // namespace navigation_components


namespace navigation_components
{

namespace action
{

namespace builder
{

class Init_Navigate_GetResult_Request_goal_id
{
public:
  Init_Navigate_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::navigation_components::action::Navigate_GetResult_Request goal_id(::navigation_components::action::Navigate_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_components::action::Navigate_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_components::action::Navigate_GetResult_Request>()
{
  return navigation_components::action::builder::Init_Navigate_GetResult_Request_goal_id();
}

}  // namespace navigation_components


namespace navigation_components
{

namespace action
{

namespace builder
{

class Init_Navigate_GetResult_Response_result
{
public:
  explicit Init_Navigate_GetResult_Response_result(::navigation_components::action::Navigate_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::navigation_components::action::Navigate_GetResult_Response result(::navigation_components::action::Navigate_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_components::action::Navigate_GetResult_Response msg_;
};

class Init_Navigate_GetResult_Response_status
{
public:
  Init_Navigate_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Navigate_GetResult_Response_result status(::navigation_components::action::Navigate_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_Navigate_GetResult_Response_result(msg_);
  }

private:
  ::navigation_components::action::Navigate_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_components::action::Navigate_GetResult_Response>()
{
  return navigation_components::action::builder::Init_Navigate_GetResult_Response_status();
}

}  // namespace navigation_components


namespace navigation_components
{

namespace action
{

namespace builder
{

class Init_Navigate_GetResult_Event_response
{
public:
  explicit Init_Navigate_GetResult_Event_response(::navigation_components::action::Navigate_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::navigation_components::action::Navigate_GetResult_Event response(::navigation_components::action::Navigate_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_components::action::Navigate_GetResult_Event msg_;
};

class Init_Navigate_GetResult_Event_request
{
public:
  explicit Init_Navigate_GetResult_Event_request(::navigation_components::action::Navigate_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_Navigate_GetResult_Event_response request(::navigation_components::action::Navigate_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_Navigate_GetResult_Event_response(msg_);
  }

private:
  ::navigation_components::action::Navigate_GetResult_Event msg_;
};

class Init_Navigate_GetResult_Event_info
{
public:
  Init_Navigate_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Navigate_GetResult_Event_request info(::navigation_components::action::Navigate_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_Navigate_GetResult_Event_request(msg_);
  }

private:
  ::navigation_components::action::Navigate_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_components::action::Navigate_GetResult_Event>()
{
  return navigation_components::action::builder::Init_Navigate_GetResult_Event_info();
}

}  // namespace navigation_components


namespace navigation_components
{

namespace action
{

namespace builder
{

class Init_Navigate_FeedbackMessage_feedback
{
public:
  explicit Init_Navigate_FeedbackMessage_feedback(::navigation_components::action::Navigate_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::navigation_components::action::Navigate_FeedbackMessage feedback(::navigation_components::action::Navigate_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_components::action::Navigate_FeedbackMessage msg_;
};

class Init_Navigate_FeedbackMessage_goal_id
{
public:
  Init_Navigate_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Navigate_FeedbackMessage_feedback goal_id(::navigation_components::action::Navigate_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Navigate_FeedbackMessage_feedback(msg_);
  }

private:
  ::navigation_components::action::Navigate_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_components::action::Navigate_FeedbackMessage>()
{
  return navigation_components::action::builder::Init_Navigate_FeedbackMessage_goal_id();
}

}  // namespace navigation_components

#endif  // NAVIGATION_COMPONENTS__ACTION__DETAIL__NAVIGATE__BUILDER_HPP_
