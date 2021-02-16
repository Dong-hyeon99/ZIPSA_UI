/**
 * @file /include/pose_sender_test/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef pose_sender_test_QNODE_HPP_
#define pose_sender_test_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <QStringListModel>

#include "living_lab_robot_moveit_client/PlanExecutePoseConstraintsAction.h"
#include "living_lab_robot_moveit_client/PlanExecutePoseConstraintsGoal.h"
#include <moveit_msgs/JointConstraint.h>

#include <tf/tf.h>
#include <tf2/LinearMath/Quaternion.h>
#include <math.h>

#include <actionlib/action_definition.h>
#include "actionlib/client/action_client.h"
#include <actionlib/client/simple_action_client.h>

#include <string>
#include <std_msgs/String.h>
#include <sstream>

/*****************************************************************************
** Namespaces
*****************************************************************************/
using namespace std;

namespace pose_sender_test {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	void run();

    living_lab_robot_moveit_client::PlanExecutePoseConstraintsGoal m_Goal;
    ros::Publisher m_intro_pub;
    ros::Publisher m_task_pub;
    ros::Subscriber m_done_sub;

   void doneCallback(const std_msgs::String::ConstPtr &msg);
    std_msgs::String m_doneData;


Q_SIGNALS:
    void rosShutdown();
    void recvDonedata();

private:
	int init_argc;
	char** init_argv;

};

}  // namespace pose_sender_test

#endif /* pose_sender_test_QNODE_HPP_ */
