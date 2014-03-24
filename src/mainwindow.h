#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "leftmenu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	LeftMenu * leftMenu;

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

signals:
	void refreshSignal();

private slots:
	void createNewTrajectorySlot();
	void createNewIsosurfaceSlot();
	void createNewMIPSlot();
	void createNewPointsSlot();
	void toggleProjectionSlot();
	void toggleSphereSlot();

private:

	void createToolBar();
};

#endif // MAINWINDOW_H
