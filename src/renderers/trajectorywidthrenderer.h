#ifndef TRAJECTORYWIDTHRENDERER_H
#define TRAJECTORYWIDTHRENDERER_H

#include "renderer.h"
#include "help/xyzvloader.h"
#include "nodes/colornode.h"
#include "nodes/node.h"

class TrajectoryWidthRenderer : public Renderer
{
	ColorNode * color;
	Node<double> * level;
public:
	TrajectoryWidthRenderer();
	virtual ~TrajectoryWidthRenderer();

	virtual QString getName() const;
	virtual QString getDesc() const;

protected:
	virtual void paintImpl();

private:
	QString cachePath;
	XYZVloader data;

	void updateSettings();
	float scaleLineWidth(float);
};


#endif // TRAJECTORYWIDTHRENDERER_H
