#ifndef VECTORRENDERER_H
#define VECTORRENDERER_H

#include "renderer.h"
#include "help/xyzloader.h"
#include "nodes/colornode.h"
#include "nodes/node.h"

class VectorRenderer : public Renderer
{
	ColorNode * color;
	Node<double> * level;
public:
	VectorRenderer();
	virtual ~VectorRenderer();

	virtual QString getName() const;
	virtual QString getDesc() const;

protected:
	virtual void paintImpl();

private:
	QString cachePath;
	XYZloader data;

	void updateSettings();
};

#endif // VECTORRENDERER_H
