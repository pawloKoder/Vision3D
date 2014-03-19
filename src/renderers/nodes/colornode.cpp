#include "colornode.h"

ColorNode::ColorNode(BrickModel* parent, QColor value, QString description) :
	Node<QColor>(parent, value, description)
{
}

ColorNode::~ColorNode()
{

}


QVariant ColorNode::decorationData(int column) const
{
	if (column == 0)
		return getValue();
	return QVariant();
}
