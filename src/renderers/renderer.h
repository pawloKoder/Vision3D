#ifndef RENDERER_H
#define RENDERER_H

#include "brickmodel.h"
#include "nodes/pathnode.h"

class Renderer : public BrickModel
{

public:
    Renderer(BrickModel * parent = 0);
	virtual ~Renderer();
	virtual QString getName() const;
	virtual QString getDesc() const;

	virtual QVariant data(int column) const;

private:
	PathNode * path;
};

#endif // RENDERER_H



