#ifndef POINTSRENDERER_H
#define POINTSRENDERER_H

#include "renderer.h"
#include "help/xyzloader.h"
#include "nodes/colornode.h"
#include "nodes/node.h"

class PointsRenderer : public Renderer
{
	ColorNode * color;
	Node<double> * level;
public:
	PointsRenderer();
	virtual ~PointsRenderer();

	virtual QString getName() const;
	virtual QString getDesc() const;

protected:
	virtual void paintImpl();

private:
	QString cachePath;
	XYZloader data;

	void updateSettings();
};

#endif // POINTSRENDERER_H
