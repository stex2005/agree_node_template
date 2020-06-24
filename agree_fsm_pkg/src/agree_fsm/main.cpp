#include "agree_fsm.h"

int main(int argc, char **argv)
{

  //Initialize ROS
  ros::init(argc, argv, "agree_fsm");

  //Create Class Object
  agree_fsm_class agree_fsm;

  //Start Spinner - Use 4 threads
  ros::MultiThreadedSpinner spinner(0);
  spinner.spin();

  return 0;
}
