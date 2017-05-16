#ifndef BUOY_SERVER_H
#define BUOY_SERVER_H

#include <ros/ros.h>

#include <actionlib_tutorials/buoyAction.h>
#include <actionlib/server/simple_action_server.h>
#include <std_msgs/Int64MultiArray.h>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
#define ALIGN_BUOY 2
#define BUOY_DETECTED 1
#define DETECT_BUOY 0
#define BUOY_ALIGNED 3

using namespace std;
using namespace cv;

typedef actionlib::SimpleActionServer<actionlib_tutorials::buoyAction> Server;

class Buoy 
{
private:
	ros::NodeHandle _n;
	Server _s;
	
	ros::Subscriber _sub;
	
	actionlib_tutorials::buoyFeedback _feedback;
	actionlib_tutorials::buoyResult _result;
	std::string _actionName;
	
	Point2f _center;
	float _radius;

public:
	Buoy(std::string _name);
	void executeCB(const actionlib_tutorials::buoyGoalConstPtr &_goal);
	void detectcallBack(const  std_msgs::Int64MultiArray::ConstPtr& num );
	void getAllignment();
	~Buoy();
};

#endif
