#include "mainwindow.h"

#include <QSplitter>
#include <QToolBar>

#include "model.h"
#include "viewsettings.h"
#include "widget/plotarea.h"
#include "renderers/renderers.h"
#include "base/strings.h"

// Images form http://cooltext.com/Logo-Design-Chrome-One

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	createToolBar();

	QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
	leftMenu = new LeftMenu();
	splitter->addWidget(leftMenu);
	PlotArea * area = new PlotArea();
	splitter->addWidget(area);
	setCentralWidget(splitter);

	connect(this, SIGNAL(refreshSignal()), area, SLOT(repaint()));
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
	tool->addAction(QIcon(":/icons/P.png"), Strings::NewPoints,
		this, SLOT(createNewPointsSlot()));
	tool->addAction(QIcon(":/icons/mesh.png"), Strings::NewMesh,
		this, SLOT(createNewMeshSlot()));
	tool->addSeparator();
	tool->addAction(QIcon(":/icons/projection.png"), Strings::ToggleProjection,
		this, SLOT(toggleProjectionSlot()));
	tool->addAction(QIcon(":/icons/sphere.png"), Strings::ToggleSphere,
		this, SLOT(toggleSphereSlot()));
	tool->addSeparator();
	tool->addAction(QIcon(":/icons/refresh.png"), Strings::Refresh,
		this, SIGNAL(refreshSignal()));

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

void MainWindow::createNewPointsSlot()
{
	Model::self().createNewView(new PointsRenderer());
}

void MainWindow::createNewMeshSlot()
{
	Model::self().createNewView(new MeshRenderer());
}

void MainWindow::toggleProjectionSlot()
{
	ViewSettings::toggleProjection();
}

void MainWindow::toggleSphereSlot()
{
	ViewSettings::toggleSphereRendering();
}
