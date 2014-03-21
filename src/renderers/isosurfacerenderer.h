#ifndef ISOSURFACERENDERER_H
#define ISOSURFACERENDERER_H

#include "renderer.h"
#include "help/xyzvloader.h"
#include "nodes/colornode.h"
#include "nodes/node.h"

class IsosurfaceRenderer : public Renderer
{
	Node<double> * level;
public:
	IsosurfaceRenderer();
	virtual ~IsosurfaceRenderer();

	virtual QString getName() const;
	virtual QString getDesc() const;

protected:
	virtual void paintImpl();

private:
	QString cachePath;
	XYZVloader data;

	void updateSettings();
};

#endif // ISOSURFACERENDERER_H
