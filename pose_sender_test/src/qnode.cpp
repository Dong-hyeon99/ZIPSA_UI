/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include "../include/pose_sender_test/qnode.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/
actionlib::SimpleActionClient<living_lab_robot_moveit_client::PlanExecutePoseConstraintsAction> *g_client;

namespace pose_sender_test {


/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init() {
	ros::init(init_argc,init_argv,"pose_sender_test");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;

    g_client = new actionlib::SimpleActionClient<living_lab_robot_moveit_client::PlanExecutePoseConstraintsAction> ("plan_and_execute_pose_w_joint_constraints",true);
    m_intro_pub = n.advertise<std_msgs::String>("wait_select_scene", 100);
    m_task_pub = n.advertise<std_msgs::String>("order_target", 100);
    m_done_sub = n.subscribe("wait_done_scene", 100, &QNode::doneCallback, this);

    start();
	return true;
}


void QNode::run() {
    ros::Rate loop_rate(33);
	while ( ros::ok() ) {
	}
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void QNode::doneCallback(const std_msgs::String::ConstPtr &msg)
{
    m_doneData = *msg;
    Q_EMIT recvDonedata();
}

}  // namespace pose_sender_test
