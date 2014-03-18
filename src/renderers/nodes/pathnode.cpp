#include "pathnode.h"

#include "../../base/filepath.h"

PathNode::PathNode(BrickModel* parent, QString value, QString description) :
	BrickModel(parent)
{
	itemData.append(QVariant::fromValue(FilePath(value)));
	itemData.append(description);

	parent->appendChild(this);
}

PathNode::~PathNode()
{

}

void PathNode::setPath(QString p)
{
	itemData[0] = QVariant::fromValue(FilePath(p));
}

QString PathNode::path() const
{
	return itemData[0].value<FilePath>().getString();
}
