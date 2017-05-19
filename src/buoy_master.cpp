#include <ros/ros.h>
#include <actionlib_tutorials/buoyAction.h>
#include <actionlib_tutorials/buoyActionFeedback.h>
#include <actionlib_tutorials/buoyActionGoal.h>
#include <actionlib_tutorials/buoyActionResult.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Float32.h>
#include <actionlib_tutorials/buoy_server.h>
#include <iostream>

using namespace std;
ros::Publisher pub_goal;
int _count =0;

void resultcallback(const  actionlib_tutorials::buoyActionResultConstPtr &num)
{
    std_msgs::Float32 val;
    val.data = num->result.sequence[_count++];

    cout<<val.data<<"data"<<endl;
    pub_goal.publish(val);


}
void feedbackcallback(const  actionlib_tutorials::buoyActionFeedbackConstPtr &num)
{
  cout<<num->feedback.sequence[0]<<endl;
}
int main(int argc, char ** argv)
{

  ros::init(argc,argv,"buoy_master");
  ros::NodeHandle n_ip;


  cout<<"initailized node"<<endl;

    pub_goal = n_ip.advertise<std_msgs::Float32>("/ip_buoy",1);
    ros::Rate loop_rate(10);
    ros::Subscriber sub_result;
    ros::Subscriber sub_feedback;


    while(ros::ok())
    {
      if(_count == 0)
      {
        std_msgs::Float32 init_val;
        init_val.data = 0;

        pub_goal.publish(init_val);
        cout<<"publish "<<init_val.data<<endl;

      }
    //  std::cout << "yo yo " << '\n';

    sub_result = n_ip.subscribe("/buoy/result",1,resultcallback);
    sub_feedback = n_ip.subscribe("/buoy/feedback",1,feedbackcallback);
    ros::spinOnce();
    loop_rate.sleep();
  }

  cout << "band ho ja" << '\n';
  return 0;
}
