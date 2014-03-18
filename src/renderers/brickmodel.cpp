#include "brickmodel.h"

#include <QDebug>

BrickModel::BrickModel(const QList<QVariant> &data, BrickModel *parent) :
    BrickModel(parent)
{
    itemData = data;
}

BrickModel::BrickModel(BrickModel *parent)
{
    parentItem = parent;
}

BrickModel::~BrickModel()
{
    qDeleteAll(childItems);
}

void BrickModel::setParent(BrickModel * brick)
{
	parentItem = brick;
}

void BrickModel::appendChild(BrickModel *item)
{
    childItems.append(item);
	item->setParent(this);
}

BrickModel *BrickModel::child(int row)
{
	return childItems.value(row);
}

int BrickModel::childCount() const
{
	return childItems.count();
}

int BrickModel::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<BrickModel*>(this));

    return 0;
}

int BrickModel::columnCount() const
{
    return itemData.count();
}

QVariant BrickModel::data(int column) const
{
	return itemData.value(column);
}

bool BrickModel::setData(int column, QVariant value)
{
	if(itemData.size() <= column)
		return false;

	itemData[column] = value;
	return true;
}

QVariant BrickModel::decorationData(int /*column*/) const
{
	return QVariant();
}

BrickModel *BrickModel::parent()
{
    return parentItem;
}
