#include "miprenderer.h"

#include <QDebug>
#include <QVector3D>
#include <GL/glu.h>

MIPrenderer::MIPrenderer()
{
	size = new Node<double>(this, 0.1, "Radius of shpere");
}

MIPrenderer::~MIPrenderer()
{
}

QString MIPrenderer::getName() const
{
	return "MIP";
}

QString MIPrenderer::getDesc() const
{
	return "MIP renderer";
}

void MIPrenderer::paintImpl()
{
	updateSettings();
	glDisable(GL_DEPTH_TEST);

	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	glPushMatrix();

	foreach(auto it, data.vertices)
	{
		glPushMatrix();

		glTranslatef(it.first.x(), it.first.y(), it.first.z());
		setColor((it.second - data.min[3]) / (data.max[3] - data.min[3]));

		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluSphere(quadric, size->getValue(), 18, 9);

		glPopMatrix();
	}

	gluDeleteQuadric(quadric);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void MIPrenderer::setColor(float ratio)
{
	QColor c = rainbow.getColor(ratio);
	glColor3f(c.redF(), c.greenF(), c.blueF());
}

void MIPrenderer::updateSettings()
{
	if(cachePath != path->getValue().getString())
	{
		cachePath = path->getValue().getString();
		data = XYZVloader(cachePath);
		data.sortByValues();
	}
}
