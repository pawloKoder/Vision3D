#include "trajectoryrenderer.h"

#include <QDebug>

TrajectoryRenderer::TrajectoryRenderer()
{
	color = new ColorNode(this);
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

void TrajectoryRenderer::paint()
{
	qDebug() << "Paint" << this;
}
