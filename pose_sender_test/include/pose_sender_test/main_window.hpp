/**
 * @file /include/pose_sender_test/main_window.hpp
 *
 * @brief Qt based gui for pose_sender_test.
 *
 * @date November 2010
 **/
#ifndef pose_sender_test_MAIN_WINDOW_H
#define pose_sender_test_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"
#include <qmessagebox.h>
/*****************************************************************************
** Namespace
*****************************************************************************/
using namespace std;
namespace pose_sender_test {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

//	void closeEvent(QCloseEvent *event); // Overloaded function


public Q_SLOTS:
    void on_pushButton_sendPos_clicked();
    void on_pushButton_clicked();
    void on_pushButton_task_clicked();
    void on_pushButton_intro_clicked();
    void sceneDone();

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
};

}  // namespace pose_sender_test

#endif // pose_sender_test_MAIN_WINDOW_H
