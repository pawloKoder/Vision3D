#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "renderer.h"
#include "help/meshloader.h"
#include "nodes/colornode.h"

class MeshRenderer : public Renderer
{
	ColorNode * color;
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	virtual QString getName() const;
	virtual QString getDesc() const;

protected:
	virtual void paintImpl();

private:
	QString cachePath;
	MeshLoader data;

	void updateSettings();
};


#endif // MESHRENDERER_H
