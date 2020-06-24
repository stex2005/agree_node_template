#include "agree_fsm.h"

/*******************/
/* ROS Main Thread */
/*******************/

void agree_fsm_class::ROS_main_thread(){
  while (ros::ok()){

    interim_state = interim_request;
    //if(interim_request==interim_state)

        //std::cout << " Ok, State: "<< interim_state << std::endl;

    if(interim_request==EXIT) ros::shutdown();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

/************************/
/* ROS Publisher Thread */
/************************/

void agree_fsm_class::ROS_publish_thread(){

  //  Declare a message and setup the publisher for that message
  std_msgs::Int64 msg;
  //  agree_smartbox_pkg::custom_msg msg;

  // Node Handler
  ros::NodeHandle n;

  // Node Rate
  ros::Rate loop_rate(100);

  // Node Publisher
  ros::Publisher agree_gui_request = n.advertise<std_msgs::Int64>("agree_gui_request",1000);

  //Variables that setup the publishing loop
  interim_request = 1;

  while (ros::ok()){

    msg.data = interim_request;
    agree_gui_request.publish(msg);
    loop_rate.sleep();
  }

}

/************************/
/* ROS Subscriber Thread */
/************************/


void agree_fsm_class::ROS_subscribe_thread(){

  //Setup a subscriber that will get data from other ROS nodes
  ros::NodeHandle n;

  ros::MultiThreadedSpinner spinner(1); // Use 4 threads

  ros::Subscriber subscriber = n.subscribe("agree_gui_status", 1000, &agree_fsm_class::ROS_subscribe_callback, this);

  spinner.spin();
}


void agree_fsm_class::ROS_keyboard_thread(){

  //Initialize Robot status
  char c;
  string inputString;
  RobotState state(STOP);
  bool swap_state(false);

  print_command_keys();

  while (ros::ok()){


    // Get character
    c = cin.get();

    if(c != '\n'){
      switch(c){

      case 's': case 'S':
        if (state != STOP)
        {
          std::cout << green_key << "Quick-swapped to STOP mode!" << color_key << std::endl;
          state = STOP;
          swap_state = true;
        }
        else
        {
          std::cout << yellow_key << "Already in STOP mode" << color_key <<  std::endl;
        }
        break;
      case 'n': case 'N':
        if (state != NULLTORQUE)
        {
          std::cout << green_key << "Quick-swapped to NULL-TORQUE mode!" << color_key << std::endl;
          state = NULLTORQUE;
          swap_state = true;
        }
        else
        {
          std::cout << yellow_key << "Already in NULL-TORQUE mode" << color_key <<  std::endl;
        }
        break;
      case 'c': case 'C':
        if (state != CURRENT)
        {
          std::cout << green_key << "Quick-swapped to CURRENT mode!" << color_key << std::endl;
          state = CURRENT;
          swap_state = true;
        }
        else
        {
          std::cout << yellow_key << "Already in CURRENT mode" << color_key <<  std::endl;
        }
        break;
      case 't': case 'T':
        if (state != TORQUE)
        {
          std::cout << green_key << "Quick-swapped to TORQUE mode!" << color_key << std::endl;
          state = TORQUE;
          swap_state = true;
        }
        else
        {
          std::cout << yellow_key << "Already in NULL-TORQUE mode" << color_key <<  std::endl;
        }
        break;

      case 'g': case 'G':
        if (state != GRAVITY)
        {
          std::cout << green_key << "Quick-swapped to GRAVITY mode!" << color_key << std::endl;
          state = GRAVITY;
          swap_state = true;
        }
        else
        {
          std::cout << yellow_key << "Already in GRAVITY mode" << color_key <<  std::endl;
        }
        break;
      case 'f': case 'F':
        if (state != FREEZE)
        {
          std::cout << green_key << "Quick-swapped to FREEZE mode!" << color_key << std::endl;
          state = FREEZE;
          swap_state = true;
        }
        else
        {
          std::cout << yellow_key << "Already in FREEZE mode" << color_key <<  std::endl;
        }
        break;
      case 'k': case 'K':

        if (state == STOP or state == EXIT)
        {   swap_state = true;
          state = EXIT;
          std::cout << yellow_key << "Ending program - no more inputs..." << color_key << std::endl;
        }
        else {
          std::cout << yellow_key << "First stop the motor" << color_key << std::endl;

        }
        break;
      case ' ':
        print_command_keys();
        break;
      default:
        std::cout << red_key << "Unrecognized key input!" << color_key <<  std::endl;
        break;
      }

      /**
                 * This is a message object. You stuff it with data, and then publish it.
                 */


      interim_request = (uint64_t) state;

      std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
    else
    {
      std::cout << yellow_key << state_labels[state] << color_key << " is the state currently active" << std::endl;
    } // else

  } // while

}


void agree_fsm_class::ROS_subscribe_callback(const std_msgs::Int64 msg)
{
  //Display data from hard real-time loop to the the terminal.
  ROS_INFO(" State:[%ld]",msg.data);
  interim_state = msg.data;
}


// Print commands on terminal
void agree_fsm_class::print_command_keys()
{
  std::cout << boldred_key << "\nCOMMAND KEYS:"<< color_key << std::endl;
  std::cout << blue_key << "\'k\'" << color_key << ": exit" << "\n";
  std::cout << blue_key << "\'s\'" << color_key << ": STOP mode"<< "\n";
  std::cout << blue_key << "\'c\'" << color_key << ": CURRENT mode"<< "\n";
  std::cout << blue_key << "\'t\'" << color_key << ": TORQUE mode"<< "\n";
  std::cout << blue_key << "\'n\'" << color_key << ": NULL-TORQUE mode" << "\n";
  std::cout << blue_key << "\'g\'" << color_key << ": GRAVITY mode"<< "\n";
  std::cout << blue_key << "\'f\'" << color_key << ": FREEZE mode"<< "\n";
  std::cout << blue_key << "\'ENTER\'" << color_key << ": SHOW current settings and command keys\n"<< "\n";
}
