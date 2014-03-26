#include "vectorrenderer.h"

#include <QDebug>
#include <QVector3D>
#include <GL/glu.h>

VectorRenderer::VectorRenderer()
{
	color = new ColorNode(this, Qt::black, "Color of arrows");
}

VectorRenderer::~VectorRenderer()
{
}

QString VectorRenderer::getName() const
{
	return "Vectors";
}

QString VectorRenderer::getDesc() const
{
	return "Vector renderer";
}

void VectorRenderer::paintImpl()
{
	updateSettings();

	glColor3f(color->getValue().redF(), color->getValue().greenF(),
		color->getValue().blueF());

	glBegin(GL_LINES);
	QVector3D prev;
	foreach(auto current, data.vertices)
	{
		glVertex3f(current.x(), current.y(), current.z());
		prev = current;
	}
	glEnd();
}

void VectorRenderer::updateSettings()
{
	if(cachePath != path->getValue().getString())
	{
		cachePath = path->getValue().getString();
		data = XYZloader(cachePath);
	}
}
