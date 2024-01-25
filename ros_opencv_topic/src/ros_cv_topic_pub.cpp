#include "ros/ros.h"                            // ROS Default Header File
#include "ros_opencv_topic/MsgOpencv.h"    // MsgTutorial Message File Header. The header file is automatically created when building the package.
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char **argv)                 // Node Main Function
{
  ros::init(argc, argv, "ros_topic_publisher");     // Initializes Node Name
  ros::NodeHandle nh;                           // Node handle declaration for communication with ROS system

  // Declare publisher, create publisher 'ros_tutorial_pub' using the 'MsgTutorial'
  // message file from the 'ros_tutorials_topic' package. The topic name is
  // 'ros_tutorial_msg' and the size of the publisher queue is set to 100.
  ros::Publisher ros_cv_topic_pub = nh.advertise<ros_opencv_topic::MsgOpencv>("ros_cv_topic_msg", 100);

  // Set the loop period. '10' refers to 10 Hz and the main loop repeats at 0.1 second intervals
  //ros::Rate loop_rate(10);

  ros_opencv_topic::MsgOpencv msg;     // Declares message 'msg' in 'MsgTutorial' message file format
  int count = 0;                            // Variable to be used in message

  cv::VideoCapture cap(0);
  cv::Mat frame; 

  int large_cont = 0;
  int large_cont_index = 0;
  cv::Rect bounding_rect;

  while (ros::ok())
  {
    cap >> frame;

    if(!frame.empty()){
      
      cv::Mat frame_hsv;
      cv::cvtColor(frame, frame_hsv, cv::COLOR_BGR2HSV);
      cv::Mat frame_mask, mask1, mask2;
      cv::inRange(frame_hsv, cv::Scalar(140, 50, 50), cv::Scalar(180, 255, 255), mask1);
      cv::inRange(frame_hsv, cv::Scalar(140, 50, 50), cv::Scalar(180, 255, 255), mask2);
      frame_mask = mask1 + mask2;
      
      std::vector<std::vector<cv::Point>> contours;
      std::vector<cv::Vec4i> hier;
      cv::findContours(frame_mask, contours, hier, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

      for(int i=0;i < contours.size(); i++){
        double a = cv::contourArea(contours[i], false);
        if(a > large_cont){
          large_cont = a;
          large_cont_index = i;
          bounding_rect = cv::boundingRect(contours[i]);
        }
      }
      try{
        cv::Scalar color(255, 0,0);
        cv::drawContours(frame, contours, large_cont_index, color, cv::FILLED, 8, hier);
      }catch (cv::Exception& e)
      {
        ROS_ERROR("draw error ");
      }
     
      cv::imshow("frame", frame);
      cv::waitKey(1);

      msg.stamp = ros::Time::now();           // Save current time in the stamp of 'msg'
      msg.data  = count;                      // Save the the 'count' value in the data of 'msg'

      ROS_INFO("send msg = %d", msg.stamp.sec);   // Prints the 'stamp.sec' message
      ROS_INFO("send msg = %d", msg.stamp.nsec);  // Prints the 'stamp.nsec' message
      ROS_INFO("send msg = %d", msg.data);        // Prints the 'data' message

      ros_cv_topic_pub.publish(msg);          // Publishes 'msg' message

      //loop_rate.sleep();                      // Goes to sleep according to the loop rate defined above.

      ++count;      
    }

                             // Increase count variable by one
  }

  return 0;
}
