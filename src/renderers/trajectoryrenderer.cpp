#include "trajectoryrenderer.h"

#include <QDebug>
#include <QVector3D>
#include <GL/glu.h>

TrajectoryRenderer::TrajectoryRenderer()
{
	color = new ColorNode(this, Qt::black, "Color of lines");
	level = new Node<double>(this, 0.1, "Max length of line");
}

TrajectoryRenderer::~TrajectoryRenderer()
{
}

QString TrajectoryRenderer::getName() const
{
	return "Trajectory";
}

QString TrajectoryRenderer::getDesc() const
{
	return "Trajectory renderer";
}

void TrajectoryRenderer::paintImpl()
{
	updateSettings();

	glColor3f(color->getValue().redF(), color->getValue().greenF(),
		color->getValue().blueF());

	glBegin(GL_LINES);
	QVector3D prev;
	foreach(auto current, data.vertices)
	{
		if((prev - current).length() > level->getValue())
		{
			glEnd();
			glBegin(GL_LINES);
		}
		glVertex3f(current.x(), current.y(), current.z());
		prev = current;
	}
	glEnd();
}

void TrajectoryRenderer::updateSettings()
{
	if(cachePath != path->getValue().getString())
	{
		cachePath = path->getValue().getString();
		data = XYZloader(cachePath);
	}
}
