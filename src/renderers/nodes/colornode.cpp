#include "colornode.h"

ColorNode::ColorNode(BrickModel* parent, QColor value, QString description) :
	BrickModel(parent)
{
	itemData.append(QVariant::fromValue(value));
	itemData.append(description);

	parent->appendChild(this);
}

ColorNode::~ColorNode()
{

}

void ColorNode::setColor(QColor c)
{
	itemData[0] = QVariant::fromValue(c);
}

QColor ColorNode::color() const
{
	return itemData[0].value<QColor>();
}

QVariant ColorNode::decorationData(int column) const
{
	if (column == 0)
		return color();
	return QVariant();
}
