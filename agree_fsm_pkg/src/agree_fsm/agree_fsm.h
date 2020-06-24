#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <thread>
#include <chrono>
#include "ros/ros.h"

//Include message types
#include "std_msgs/Int64.h"
//#include "agree_smartbox_pkg/"custom_msg.h"

//Include threads
#include <boost/thread/thread.hpp>

using namespace std;

// Text Color Identifiers
const string boldred_key = "\033[1;31m";
const string red_key = "\033[31m";
const string boldpurple_key = "\033[1;35m";
const string yellow_key = "\033[33m";
const string blue_key = "\033[36m";
const string green_key = "\033[32m";
const string color_key = "\033[0m";

//Labels for states
const string state_labels[] = {
  "EXIT",
  "STOP",
  "CURRENT",
  "TORQUE",
  "NULLTORQUE",
  "GRAVITY",
  "FREEZE",
  "QUIT",
};

enum RobotState
{
  EXIT,
  STOP,
  CURRENT,
  TORQUE,
  NULLTORQUE,
  GRAVITY,
  FREEZE,
  QUIT,
};

class agree_fsm_class
{
public:
  agree_fsm_class()
  {
    boost_ROS_publish_thread    = boost::thread(&agree_fsm_class::ROS_publish_thread, this);
    boost_ROS_subscribe_thread  = boost::thread(&agree_fsm_class::ROS_subscribe_thread, this);
    boost_ROS_keyboard_thread   = boost::thread(&agree_fsm_class::ROS_keyboard_thread, this);
    boost_ROS_main_thread       = boost::thread(&agree_fsm_class::ROS_main_thread, this);
    std::cout << "ROS interface objects instantiated" << std::endl;

  }

  ~agree_fsm_class()
  {
    std::cout << "ROS interface threads joining" << std::endl;
    boost_ROS_publish_thread.join();
    boost_ROS_subscribe_thread.join();
    //boost_ROS_keyboard_thread.join();
    boost_ROS_main_thread.join();
  }

  uint64_t interim_state;
  uint64_t interim_request;

private:

  boost::thread boost_ROS_publish_thread;
  boost::thread boost_ROS_subscribe_thread;
  boost::thread boost_ROS_keyboard_thread;
  boost::thread boost_ROS_main_thread;

  void ROS_subscribe_thread();
  void ROS_publish_thread();
  void ROS_keyboard_thread();
  void ROS_main_thread();

  void ROS_subscribe_callback(const std_msgs::Int64 msg);
  void print_command_keys();


};


#endif // INTERFACE_H
