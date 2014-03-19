#include "renderer.h"

#include <QDebug>

Renderer::Renderer(BrickModel * parent) :
    BrickModel(parent)
{
	itemData.append("Test");
	itemData.append("LOl");

	path = new Node<FilePath>(this, FilePath(""), "Data path");
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

QString Renderer::getName() const
{
	return "Renderer";
}

QString Renderer::getDesc() const
{
	return "Default renderer";
}


