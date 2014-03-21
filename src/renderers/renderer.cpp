#include "renderer.h"

#include <QDebug>

Renderer::Renderer(BrickModel * parent) :
    BrickModel(parent)
{
	itemData.append("Test");
	itemData.append("LOl");

	path = new FilePathNode(this, FilePath(""), "Data path");
	print = new Node<bool>(this, true, "Enable/Disable painting");
}

Renderer::~Renderer()
{

}

QVariant Renderer::data(int column) const
{
	switch(column)
	{
		case 0:
			return getName();
		case 1:
			return getDesc();
		default:
			return BrickModel::data(column);
	}
}

void Renderer::paint()
{
	if(print->getValue())
		paintImpl();
}

QString Renderer::getName() const
{
	return "Renderer";
}

QString Renderer::getDesc() const
{
	return "Default renderer";
}


