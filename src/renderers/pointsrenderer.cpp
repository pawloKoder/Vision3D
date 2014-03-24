#include "pointsrenderer.h"

#include <QDebug>
#include <QVector3D>
#include <GL/glu.h>

PointsRenderer::PointsRenderer()
{
	color = new ColorNode(this, Qt::black, "Color of points");
}

PointsRenderer::~PointsRenderer()
{
}

QString PointsRenderer::getName() const
{
	return "Points";
}

QString PointsRenderer::getDesc() const
{
	return "Points renderer";
}

void PointsRenderer::paintImpl()
{
	updateSettings();

	glColor3f(color->getValue().redF(), color->getValue().greenF(),
		color->getValue().blueF());

	glBegin(GL_POINTS);
	QVector3D prev;
	foreach(auto current, data.vertices)
	{
		glVertex3f(current.x(), current.y(), current.z());
		prev = current;
	}
	glEnd();
}

void PointsRenderer::updateSettings()
{
	if(cachePath != path->getValue().getString())
	{
		cachePath = path->getValue().getString();
		data = XYZloader(cachePath);
	}
}
