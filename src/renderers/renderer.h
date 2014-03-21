#ifndef RENDERER_H
#define RENDERER_H

#include "brickmodel.h"
#include "nodes/node.h"
#include "nodes/filepathnode.h"
#include "../base/filepath.h"

class Renderer : public BrickModel
{

public:
	Renderer(BrickModel * parent = nullptr);
	virtual ~Renderer();
	virtual QString getName() const;
	virtual QString getDesc() const;

	virtual QVariant data(int column) const;

	void paint();

protected:
	FilePathNode * path;
	Node<bool> * print;

	virtual void paintImpl() = 0;
};

#endif // RENDERER_H



