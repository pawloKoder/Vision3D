#ifndef TRAJECTORYRENDERER_H
#define TRAJECTORYRENDERER_H

#include "renderer.h"
#include "nodes/colornode.h"

class TrajectoryRenderer : public Renderer
{
	ColorNode * color;
public:
	TrajectoryRenderer();
	virtual ~TrajectoryRenderer();

	virtual QString getName() const;
	virtual QString getDesc() const;
};

#endif // TRAJECTORYRENDERER_H
