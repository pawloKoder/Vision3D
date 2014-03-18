#include "mainwindow.h"

#include <QSplitter>
#include <QToolBar>

#include "model.h"
#include "widget/plotarea.h"
#include "renderers/renderers.h"
#include "widget/filepicker.h"
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
	tool->addAction(QIcon(":/icons/addIcon.png"), "NewView",
					this, SLOT(createNewViewSlot()));

	addToolBar(tool);
}

void MainWindow::createNewViewSlot()
{
	Model::self().createNewView(new TrajectoryRenderer());
}
