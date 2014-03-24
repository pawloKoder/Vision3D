#include "meshrenderer.h"

#include <QDebug>
#include <QVector3D>
#include <GL/glu.h>

MeshRenderer::MeshRenderer()
{
	color = new ColorNode(this, Qt::black, "Color of lines");
}

MeshRenderer::~MeshRenderer()
{
}

QString MeshRenderer::getName() const
{
	return "Mesh";
}

QString MeshRenderer::getDesc() const
{
	return "Mesh renderer";
}

void MeshRenderer::paintImpl()
{
	updateSettings();

	glColor3f(color->getValue().redF(), color->getValue().greenF(),
		color->getValue().blueF());

	foreach(auto current, data.walls)
	{
		glBegin(GL_LINE_STRIP);
		for(int i = 0; i < 4; ++i)
			glVertex3f(data.nodes[current.nodes[i]].x(),
				data.nodes[current.nodes[i]].y(),
				data.nodes[current.nodes[i]].z());
		glEnd();
	}
}

void MeshRenderer::updateSettings()
{
	if(cachePath != path->getValue().getString())
	{
		cachePath = path->getValue().getString();
		data = MeshLoader(cachePath);
	}
}
