#include <ros/ros.h>
#include <actionlib_tutorials/buoyAction.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <std_msgs/Int64MultiArray.h>
#include <actionlib_tutorials/buoy_server.h>
#include <iostream>

using namespace std;


typedef actionlib::SimpleActionClient<actionlib_tutorials::buoyAction> Client;

 class client_cb
{
private:
	Client _client;
	//actionlib_tutorials::buoyGoal _goal;
	

public:
	
	void set_client(Client c)
	{
		_client =c;
	}
	/*	
	void set_goal(actionlib_tutorials::buoyGoal goal)
	{
		_goal=goal;
	}/*
	void set_client(int a)
	{
		_a=a;
	}
	void set_goal(int b)
	{
		_b=b;
	}*/
	void goalcallback(const  std_msgs::Int64MultiArray::ConstPtr &num );

} ;

void client_cb::goalcallback(const  std_msgs::Int64MultiArray::ConstPtr &num)
{
	ROS_INFO("\nCenter: %ld , %ld :: order: %ld :: angle :%ld ", num->data[0], num->data[1], num->data[2],num->data[3]);
	
	//cout<<_a<<"  "<<_b<<endl;
    
	/*
	if(num->data[2]==DETECT_BUOY)
	{
		_goal.order = DETECT_BUOY;
		ROS_INFO("Sending goal - DETECT_BUOY.");
    	_client.sendGoal(_goal);

    	 bool _actionStatus = _client.waitForResult(ros::Duration(300.0));

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


	} 

	if(num->data[2]==ALIGN_BUOY)
	{
		_goal.order = ALIGN_BUOY;

		ROS_INFO("Sending goal - ALIGN_BUOY");
	    _goal.order = ALIGN_BUOY;
	    _client.sendGoal(_goal);
	    bool _actionStatus = _client.waitForResult(ros::Duration(300.0));

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
		
	}	*/
	
}

int main(int argc, char ** argv)
{

	int _count = 0 ;
    ros::init(argc, argv, "buoy_client");

    ros::NodeHandle _it;

    
    Client _client("buoy",true);
    /*
    ROS_INFO("buoy_client started. Waiting for buoy_server.");
    _client.waitForServer();
    ROS_INFO("buoy_server started.");
    actionlib_tutorials::buoyGoal _goal;
    _goal.order = DETECT_BUOY;
    ROS_INFO("Sending goal - DETECT_BUOY.");
    _client.sendGoal(_goal);
    bool _actionStatus = _client.waitForResult(ros::Duration(300.0));

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
    /*
    ROS_INFO("Sending goal - ALIGN_BUOY");
    _goal.order = ALIGN_BUOY;
    _client.sendGoal(_goal);
    _actionStatus = _client.waitForResult(ros::Duration(300.0));

    if(_actionStatus == true)
    {
        actionlib::SimpleClientGoalState _state = _client.getState();
        ROS_INFO("buoy_client : Action finished - %s",_state.toString().c_str());
    }
    else
    {
        ROS_INFO("buoy_client : Action did not finish within the specified time.");
        _client.cancelGoal();
    }*/

    client_cb cli;
    cli.set_client(_client);
   // cli.set_goal(_goal);
    
   ros::Subscriber sub = _it.subscribe("/buoy/feedback", 1, &client_cb::goalcallback, &cli);
   ros::spin();

    return 0;
}
