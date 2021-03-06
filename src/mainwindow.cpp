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
	setWindowTitle("Vision3D");

	createToolBar();

	QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
	leftMenu = new LeftMenu();
	splitter->addWidget(leftMenu);
	PlotArea * area = new PlotArea();
	splitter->addWidget(area);
	setCentralWidget(splitter);

	connect(this, SIGNAL(refreshSignal()), area, SLOT(repaint()));

	resize(800, 600);

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
	tool->addAction(QIcon(":/icons/V.png"), Strings::NewVector,
		this, SLOT(createNewVectorSlot()));
	tool->addAction(QIcon(":/icons/Tw.png"), Strings::NewTajectoryWidth,
		this, SLOT(createNewTrajectoryWidthSlot()));
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
	tool->addSeparator();
	tool->addAction(QIcon(":/icons/V1.png"), Strings::Front,
		this, SLOT(resetViewFrontSlot()));
	tool->addAction(QIcon(":/icons/V2.png"), Strings::Top,
		this, SLOT(resetViewTopSlot()));
	tool->addAction(QIcon(":/icons/V3.png"), Strings::Side,
		this, SLOT(resetViewSideSlot()));

	addToolBar(tool);
}

void MainWindow::createNewTrajectorySlot()
{
	Model::self().createNewView(new TrajectoryRenderer());
}

void MainWindow::createNewTrajectoryWidthSlot()
{
	Model::self().createNewView(new TrajectoryWidthRenderer());
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

void MainWindow::createNewVectorSlot()
{
	Model::self().createNewView(new VectorRenderer());
}

void MainWindow::toggleProjectionSlot()
{
	ViewSettings::toggleProjection();
	emit refreshSignal();
}

void MainWindow::toggleSphereSlot()
{
	ViewSettings::toggleSphereRendering();
	emit refreshSignal();
}

void MainWindow::resetViewFrontSlot()
{
	ViewSettings::resetViewFront();
	emit refreshSignal();
}

void MainWindow::resetViewTopSlot()
{
	ViewSettings::resetViewTop();
	emit refreshSignal();
}

void MainWindow::resetViewSideSlot()
{
	ViewSettings::resetViewSide();
	emit refreshSignal();
}
