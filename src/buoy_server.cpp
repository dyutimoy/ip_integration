#include <ros/ros.h>
#include <actionlib_tutorials/buoy_server.h>
#define PI 3.1414
#include <iostream>
//ek file may sequence of goals has to defined
/* This is server for image detection
	step 1 bouy detection
	step 2 allignment
	the feedback are whether to rotate aur not
	angle and x and y


 */
using namespace std;

Buoy::Buoy(string name) : _s(_n, name, boost::bind(&Buoy::executeCB, this, _1), false), _actionName(name)
{
	_sub =_n.subscribe("state",1,&Buoy::detectcallBack,this);
	cout<<"chal ja"<<endl;
	_s.start();
	cout<<"ky hua"<<endl;

}
//started the server


void Buoy::detectcallBack(const std_msgs::Int64MultiArray::ConstPtr &num)
{
	ROS_INFO("\nCentre: %ld , %d :: Radius: %ld ", num->data[0], num->data[1], num->data[2]);
	_radius=num->data[2];
	_center.x=num->data[0];
	_center.y=num->data[1];
}
//setting aur parameters

void Buoy::executeCB(const actionlib_tutorials::buoyGoalConstPtr &_goal)
{
	cout<<"kuch ho rahha hai"<<endl;
	ros::Rate looprate(10);
	bool success =true;
	cout<<"kuch ho rahha rrrrrr hai"<<endl;
	switch(_goal->order)
	{
		case DETECT_BUOY:
        {
            int _detected;

            while(ros::ok())
            {
                if (_s.isPreemptRequested() || !ros::ok())
                {
                    ROS_INFO("%s: Preempted", _actionName.c_str());
                    _s.setPreempted();
                    success = false;
                    break;
                }

                _detected = _radius;

				if(_detected != 0)
				{
					_result.sequence.push_back(BUOY_DETECTED);
					_s.setSucceeded(_result);
					_feedback.sequence.clear();
					_feedback.sequence.push_back(1);
					_feedback.sequence.push_back(0);
					_feedback.sequence.push_back(BUOY_DETECTED);
					_feedback.sequence.push_back(0);
					break;
				}
				else
				{
					_feedback.sequence.clear();
					_feedback.sequence.push_back(0);
					_feedback.sequence.push_back(0);
					_feedback.sequence.push_back(DETECT_BUOY);
					_feedback.sequence.push_back(180);

				}
				_s.publishFeedback(_feedback);
				looprate.sleep();
            }

            break;
        }
		case ALIGN_BUOY:
		{
			int _detected;
			_detected =_radius;
			while(ros::ok())
			{
				if (_s.isPreemptRequested() || !ros::ok())
                {
                    ROS_INFO("%s: Preempted", _actionName.c_str());
                    _s.setPreempted();
                    success = false;
                    break;
                }

                if(_detected != 0)
                {
                	getAllignment();


                	if((_feedback.sequence[2] < 5 && _feedback.sequence[2] > -5) && (_feedback.sequence[3] > -5 && _feedback.sequence[3] < 5) && _feedback.sequence[1] != 180)
                	{
										_feedback.sequence.clear();
                		_feedback.sequence.push_back(BUOY_ALIGNED);
                		_feedback.sequence.push_back(0);
                		_result.sequence.push_back(BUOY_ALIGNED);
                		_s.setSucceeded(_result);

                   		break;
                	}
                	else {
                		_feedback.sequence.push_back(ALIGN_BUOY);
                		_feedback.sequence.push_back(10);
                	}
                }
                else
               	{
									_feedback.sequence.clear();
					_feedback.sequence.push_back(0);
					_feedback.sequence.push_back(0);
					_feedback.sequence.push_back(DETECT_BUOY);
					_feedback.sequence.push_back(180);
					_result.sequence.push_back(DETECT_BUOY);
                	_s.setSucceeded(_result);


                }

                _s.publishFeedback(_feedback);
                looprate.sleep();

			}
			break;
		}

	}

}

void Buoy::getAllignment()
{
	_feedback.sequence.clear();
	_feedback.sequence.push_back(480/2 - _center.x);
	_feedback.sequence.push_back(640/2-_center.y);
	 cout<< _feedback.sequence[0]<< " : " << _feedback.sequence[1] << endl;

}


Buoy::~Buoy()
{
}

int main(int argc,char ** argv)
{
	ROS_INFO("Starting node");
    ros::init(argc, argv, "buoy_server");
    Buoy _buoyserver("buoy");
    ros::spin();
    return 0;
}
