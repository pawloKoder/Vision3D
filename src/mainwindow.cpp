#include "mainwindow.h"

#include <QSplitter>
#include <QToolBar>

#include "model.h"
#include "viewsettings.h"
#include "widget/plotarea.h"
#include "renderers/renderers.h"
#include "base/strings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
	createToolBar();

	QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
	leftMenu = new LeftMenu();
	splitter->addWidget(leftMenu);
	splitter->addWidget(new PlotArea());
	setCentralWidget(splitter);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createToolBar()
{
	QToolBar *tool = new QToolBar("Actions");
	tool->addAction(QIcon(":/icons/T.png"), Strings::NewTajectory,
		this, SLOT(createNewTrajectorySlot()));
	tool->addAction(QIcon(":/icons/I.png"), Strings::NewIsosurface,
		this, SLOT(createNewIsosurfaceSlot()));
	tool->addAction(QIcon(":/icons/M.png"), Strings::NewMIP,
		this, SLOT(createNewMIPSlot()));
	tool->addSeparator();
	tool->addAction(QIcon(":/icons/projection.png"), Strings::ToggleProjection,
		this, SLOT(toggleProjectionSlot()));

	addToolBar(tool);
}

void MainWindow::createNewTrajectorySlot()
{
	Model::self().createNewView(new TrajectoryRenderer());
}

void MainWindow::createNewIsosurfaceSlot()
{
	Model::self().createNewView(new IsosurfaceRenderer());
}

void MainWindow::createNewMIPSlot()
{
	Model::self().createNewView(new MIPrenderer());
}

void MainWindow::toggleProjectionSlot()
{
	ViewSettings::toggleProjection();
}
