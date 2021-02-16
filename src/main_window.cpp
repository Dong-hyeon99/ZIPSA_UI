/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/pose_sender_test/main_window.hpp"
#include <iostream>
#include <std_msgs/String.h>
#include <sstream>

extern actionlib::SimpleActionClient<living_lab_robot_moveit_client::PlanExecutePoseConstraintsAction> *g_client;
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace pose_sender_test {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , qnode(argc,argv)
{
    ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
    qnode.init();

}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/
void MainWindow::on_pushButton_clicked()
{
    system("rosrun turtlesim turtlesim_node");
}

void MainWindow::on_pushButton_sendPos_clicked()
{
    living_lab_robot_moveit_client::PlanExecutePoseConstraintsGoal goal;

    g_client->waitForServer();

    goal.target_pose.header.frame_id = ui.lineEdit_FrameID->text().toStdString();
    goal.target_pose.pose.position.x = ui.lineEdit_X->text().toDouble();
    goal.target_pose.pose.position.y = ui.lineEdit_Y->text().toDouble();
    goal.target_pose.pose.position.z = ui.lineEdit_Z->text().toDouble();

    double theta = atan2(goal.target_pose.pose.position.y, goal.target_pose.pose.position.x);
    tf2::Quaternion quat;
    quat.setRPY(0.0, 0.0, theta);

    goal.target_pose.pose.orientation.x = quat.getX();
    goal.target_pose.pose.orientation.y = quat.getY();
    goal.target_pose.pose.orientation.z = quat.getZ();
    goal.target_pose.pose.orientation.w = quat.getW();

    moveit_msgs::JointConstraint joint_constraint_arm1_joint;
    joint_constraint_arm1_joint.joint_name = "arm1_joint";
    joint_constraint_arm1_joint.position = float(0.0);
    joint_constraint_arm1_joint.tolerance_above = float(30) * M_PI / 180.0;
    joint_constraint_arm1_joint.tolerance_below = float(30) * M_PI / 180.0;
    joint_constraint_arm1_joint.weight = 1.0;

    moveit_msgs::JointConstraint joint_constraint_arm6_joint;
    joint_constraint_arm6_joint.joint_name = "arm6_joint";
    joint_constraint_arm6_joint.position = float(0.0);
    joint_constraint_arm6_joint.tolerance_above = float(10) * M_PI / 180.0;
    joint_constraint_arm6_joint.tolerance_below = float(10) * M_PI / 180.0;
    joint_constraint_arm6_joint.weight = 1.0;

    goal.joint_constraints.push_back(joint_constraint_arm1_joint);
    goal.joint_constraints.push_back(joint_constraint_arm6_joint);

    g_client->sendGoal(goal);
    g_client->waitForResult();

    cout<<"g_client->getResult(): "<<(*g_client->getResult())<<endl;

}

void MainWindow::on_pushButton_task_clicked()
{
    std_msgs::String msg;
    msg.data = ui.lineEdit_task->text().toStdString();
    qnode.m_task_pub.publish(msg);
}


void MainWindow::on_pushButton_intro_clicked()
{
    std_msgs::String msg;
    msg.data = ui.comboBox_scene->currentText().toStdString();
    qnode.m_intro_pub.publish(msg);
}

}  // namespace pose_sender_test



