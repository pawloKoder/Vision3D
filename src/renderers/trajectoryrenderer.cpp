#include "trajectoryrenderer.h"

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
