#include <ros/ros.h>
#include <actionlib_tutorials/buoyAction.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <std_msgs/Int64.h>
#include <std_msgs/Float32.h>
#include <actionlib_tutorials/buoy_server.h>
#include <iostream>

using namespace std;


typedef actionlib::SimpleActionClient<actionlib_tutorials::buoyAction> Client;


void goalcallback(const  std_msgs::Float32::ConstPtr &num)
{
	int temp = (int)num->data;
	cout<<(int)num->data<<"data "<<temp<<endl;
	if(temp==1)
	{
		Client _client("buoy",true);
		ROS_INFO("buoy_client started. Waiting for buoy_server.");
		_client.waitForServer();
		ROS_INFO("buoy_server started.");
		actionlib_tutorials::buoyGoal _goal;
		_goal.order = ALIGN_BUOY;
		ROS_INFO("Sending goal - ALIGN_BUOY.");
		_client.sendGoal(_goal);
		bool _actionStatus = _client.waitForResult(ros::Duration(300.0));
		cout<<_actionStatus<<endl;
		if(_actionStatus == true)
		{
		    actionlib::SimpleClientGoalState _state = _client.getState();
		    ROS_INFO("buoy_client : Action finished - %s",_state.toString().c_str());
		}
		else
		{
		    ROS_INFO("buoy_client : Action did not finish within the specified time.");
		    _client.cancelGoal();
		}
	}		//~_client();

}

int main(int argc, char ** argv)
{

	int _count = 0 ;
    ros::init(argc, argv, "buoy_align_client");

    ros::NodeHandle _it;
    cout<<" intialized node"<<endl;
    ros::Subscriber sub = _it.subscribe("/ip_buoy", 1, goalcallback);
    _count++;
    cout<<_count<<endl;


   ros::spin();

    return 0;
}
