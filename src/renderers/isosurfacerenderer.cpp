#include "isosurfacerenderer.h"

#include <QDebug>
#include <QVector3D>
#include <GL/glu.h>

IsosurfaceRenderer::IsosurfaceRenderer()
{
	level = new Node<double>(this, 0.1, "ValueOfIsosurface");
}

IsosurfaceRenderer::~IsosurfaceRenderer()
{
}

QString IsosurfaceRenderer::getName() const
{
	return "Isosurface";
}

QString IsosurfaceRenderer::getDesc() const
{
	return "Isosurface renderer";
}

void IsosurfaceRenderer::paintImpl()
{
	updateSettings();

	glBegin(GL_LINES);
	QVector3D prev;
	foreach(auto current, data.vertices)
	{
		if((prev - current.first).length() > level->getValue())
		{
			glEnd();
			glBegin(GL_LINES);
		}
		glVertex3f(current.first.x(), current.first.y(), current.first.z());
		prev = current.first;
	}
	glEnd();
}

void IsosurfaceRenderer::updateSettings()
{
	if(cachePath != path->getValue().getString())
	{
		cachePath = path->getValue().getString();
		data = XYZVloader(cachePath);
	}
}
