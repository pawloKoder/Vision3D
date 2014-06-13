#include "trajectorywidthrenderer.h"

#include <QDebug>
#include <QVector3D>
#include <GL/glu.h>

TrajectoryWidthRenderer::TrajectoryWidthRenderer()
{
	color = new ColorNode(this, Qt::black, "Color of lines");
	level = new Node<double>(this, 0.1, "Max length of line");
}

TrajectoryWidthRenderer::~TrajectoryWidthRenderer()
{
}

QString TrajectoryWidthRenderer::getName() const
{
	return "TrajectoryWidth";
}

QString TrajectoryWidthRenderer::getDesc() const
{
	return "Trajectory width renderer";
}

void TrajectoryWidthRenderer::paintImpl()
{
	updateSettings();

	glColor3f(color->getValue().redF(), color->getValue().greenF(),
		color->getValue().blueF());

	glLineWidth(0.1);
	QVector3D prev;
	foreach(auto current, data.vertices)
	{
		if((prev - current.first).length() > level->getValue())
		{
			//glEnd();
			//glLineWidth(0.3);
			//glBegin(GL_LINE_STRIP);
		}
		else
		{
			glLineWidth(scaleLineWidth(current.second));
			glBegin(GL_LINES);
			glVertex3f(current.first.x(), current.first.y(), current.first.z());
			glVertex3f(prev.x(), prev.y(), prev.z());
			glEnd();
		}
		prev = current.first;
	}

	glLineWidth(0);
	glEnd();
}

void TrajectoryWidthRenderer::updateSettings()
{
	if(cachePath != path->getValue().getString())
	{
		cachePath = path->getValue().getString();
		data = XYZVloader(cachePath);
	}
}

float TrajectoryWidthRenderer::scaleLineWidth(float x)
{
	float max = 2;
	float min = 0;
	float maxValue = qMax(qAbs(data.max[3]), qAbs(data.min[3]));
	float minValue = qMin(0.0f, qMin(qAbs(data.max[3]), qAbs(data.min[3])));

	return min + (max - min) * (maxValue - qAbs(x)) / (maxValue - minValue);
}
