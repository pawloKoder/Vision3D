#include "plotarea.h"

#include <QMouseEvent>
#include <QObject>

#include "GL/glu.h"
#include "../model.h"
#include "../viewsettings.h"

PlotArea::PlotArea(QWidget *parent) :
	QGLWidget(parent)
{
	connect(this, SIGNAL(mouseMove(QPoint)), &ViewSettings::self(), SLOT(mouseMove(QPoint)));
	connect(this, SIGNAL(wheelDelta(int)), &ViewSettings::self(), SLOT(wheelDelta(int)));
	connect(this, SIGNAL(mouseMove(QPoint)), this, SLOT(repaint()));
	connect(this, SIGNAL(wheelDelta(int)), this, SLOT(repaint()));
}

PlotArea::~PlotArea()
{
}

void PlotArea::setViewData(ViewData data)
{
	view = data;
	emit update();
}

void PlotArea::initializeGL()
{
	paintGL();
}

void PlotArea::resizeGL(int w, int h)
{
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	float Sx =(GLint)w;
	float Sy =(GLint)h;
	glViewport(0, 0, Sx, Sy);

	float ratio = Sx/Sy;

	gluPerspective(35.0,ratio,0.1f,1000.0f);

	paintGL();
}

void PlotArea::paintGL()
{
	view = ViewSettings::getViewData();

	clear();
	computeView();

	Model::paintAll();

	glColor3f(0.0,0.0,0.0);
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_LINE );
	gluSphere( quadric ,  50.0*(0.01+view.zoom) , 18 , 9 );
}

void PlotArea::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.7, 0.7, 1.0, 1.0);
}

void PlotArea::computeView()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float pi = 4.0*atan(1);
	float alpha = pi*view.rotation[0];
	float beta = 2*pi*view.rotation[1];

	position = QVector3D(cos(alpha)*sin(beta),sin(alpha),cos(alpha)*cos(beta));
	direction = - position;
	float mode = 100.0*(0.01+view.zoom);
	position *= mode;

	up = QVector3D(sin(alpha)*sin(beta),-cos(alpha),sin(alpha)*cos(beta));

	gluLookAt(position.x(),position.y(),position.z(),
			0,0,0,
			  up.x(),up.y(),up.z());

	glLineWidth(4.0);
	glBegin(GL_LINES);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(position.x(),position.y(),position.z());
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(3*sin(alpha)*sin(beta),3*(-cos(alpha)),3*sin(alpha)*cos(beta));
	glEnd();
	glLineWidth(1.0);
}

void PlotArea::mouseMoveEvent(QMouseEvent* event){
	static bool drag = false;
	static QPoint position = event->pos();

	if(event->buttons() & Qt::LeftButton)
	{
		if(drag)
		{
			emit mouseMove(event->pos()-position);
		}
		drag = true;
		position = event->pos();
	}
	else
		drag = false;
}

void PlotArea::wheelEvent(QWheelEvent *event)
{
	emit wheelDelta(event->delta());
}
