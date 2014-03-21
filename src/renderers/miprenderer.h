#ifndef MIPRENDERER_H
#define MIPRENDERER_H

#include "renderer.h"
#include "help/xyzvloader.h"
#include "nodes/node.h"

class MIPrenderer : public Renderer
{
public:
	MIPrenderer();
	virtual ~MIPrenderer();

	virtual QString getName() const;
	virtual QString getDesc() const;

private:
	virtual void paintImpl();

private:
	QString cachePath;
	XYZVloader data;
	Node<double> * size;

	void updateSettings();
	void setColor(float ratio);
};

#endif // MIPRENDERER_H
