// Generated by gencpp from file ur_dashboard_msgs/GetRobotMode.msg
// DO NOT EDIT!


#ifndef UR_DASHBOARD_MSGS_MESSAGE_GETROBOTMODE_H
#define UR_DASHBOARD_MSGS_MESSAGE_GETROBOTMODE_H

#include <ros/service_traits.h>


#include <ur_dashboard_msgs/GetRobotModeRequest.h>
#include <ur_dashboard_msgs/GetRobotModeResponse.h>


namespace ur_dashboard_msgs
{

struct GetRobotMode
{

typedef GetRobotModeRequest Request;
typedef GetRobotModeResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct GetRobotMode
} // namespace ur_dashboard_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::ur_dashboard_msgs::GetRobotMode > {
  static const char* value()
  {
    return "ef94c03da2e53bb8c576236bb003fe8a";
  }

  static const char* value(const ::ur_dashboard_msgs::GetRobotMode&) { return value(); }
};

template<>
struct DataType< ::ur_dashboard_msgs::GetRobotMode > {
  static const char* value()
  {
    return "ur_dashboard_msgs/GetRobotMode";
  }

  static const char* value(const ::ur_dashboard_msgs::GetRobotMode&) { return value(); }
};


// service_traits::MD5Sum< ::ur_dashboard_msgs::GetRobotModeRequest> should match
// service_traits::MD5Sum< ::ur_dashboard_msgs::GetRobotMode >
template<>
struct MD5Sum< ::ur_dashboard_msgs::GetRobotModeRequest>
{
  static const char* value()
  {
    return MD5Sum< ::ur_dashboard_msgs::GetRobotMode >::value();
  }
  static const char* value(const ::ur_dashboard_msgs::GetRobotModeRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::ur_dashboard_msgs::GetRobotModeRequest> should match
// service_traits::DataType< ::ur_dashboard_msgs::GetRobotMode >
template<>
struct DataType< ::ur_dashboard_msgs::GetRobotModeRequest>
{
  static const char* value()
  {
    return DataType< ::ur_dashboard_msgs::GetRobotMode >::value();
  }
  static const char* value(const ::ur_dashboard_msgs::GetRobotModeRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::ur_dashboard_msgs::GetRobotModeResponse> should match
// service_traits::MD5Sum< ::ur_dashboard_msgs::GetRobotMode >
template<>
struct MD5Sum< ::ur_dashboard_msgs::GetRobotModeResponse>
{
  static const char* value()
  {
    return MD5Sum< ::ur_dashboard_msgs::GetRobotMode >::value();
  }
  static const char* value(const ::ur_dashboard_msgs::GetRobotModeResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::ur_dashboard_msgs::GetRobotModeResponse> should match
// service_traits::DataType< ::ur_dashboard_msgs::GetRobotMode >
template<>
struct DataType< ::ur_dashboard_msgs::GetRobotModeResponse>
{
  static const char* value()
  {
    return DataType< ::ur_dashboard_msgs::GetRobotMode >::value();
  }
  static const char* value(const ::ur_dashboard_msgs::GetRobotModeResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // UR_DASHBOARD_MSGS_MESSAGE_GETROBOTMODE_H
