#ifndef TRAJECTORYRENDERER_H
#define TRAJECTORYRENDERER_H

#include "renderer.h"
#include "help/xyzloader.h"
#include "nodes/colornode.h"
#include "nodes/node.h"

class TrajectoryRenderer : public Renderer
{
	ColorNode * color;
	Node<double> * level;
public:
	TrajectoryRenderer();
	virtual ~TrajectoryRenderer();

	virtual QString getName() const;
	virtual QString getDesc() const;

protected:
	virtual void paintImpl();

private:
	QString cachePath;
	XYZloader data;

	void updateSettings();
};

#endif // TRAJECTORYRENDERER_H
