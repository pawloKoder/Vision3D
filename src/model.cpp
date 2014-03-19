#include "model.h"

#include <QDebug>

#include "renderers/renderer.h"
#include "renderers/brickmodel.h"

Model & Model::self()
{
	static Model instance;
	return instance;
}

Model::Model(QObject *parent) :
	QAbstractItemModel(parent)
{
	QList<QVariant> rootData;
	rootData << "Title" << "Summary";
	rootItem = new BrickModel(rootData);
}

Model::~Model()
{
	delete rootItem;
}

void Model::createNewView(Renderer * renderer)
{
	int count = rootItem->columnCount();
	beginInsertRows(index(0, count), 0, 1);
	rootItem->appendChild(renderer);
	endInsertRows();
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent)
	const
 {
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	BrickModel *parentItem;

	if (!parent.isValid())
		parentItem = rootItem;
	else
		parentItem = static_cast<BrickModel*>(parent.internalPointer());

	BrickModel *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
 }

QModelIndex Model::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	BrickModel *childItem = static_cast<BrickModel*>(index.internalPointer());
	BrickModel *parentItem = childItem->parent();

	if (parentItem == rootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

int Model::rowCount(const QModelIndex &parent) const
{
	BrickModel *parentItem;
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		parentItem = rootItem;
	else
		parentItem = static_cast<BrickModel*>(parent.internalPointer());

	return parentItem->childCount();
}

int Model::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return static_cast<BrickModel*>(parent.internalPointer())->columnCount();
	else
		return rootItem->columnCount();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	BrickModel *item = static_cast<BrickModel*>(index.internalPointer());

	switch(role)
	{
	case Qt::DisplayRole :
		return item->data(index.column());
	case Qt::DecorationRole :
		return item->decorationData(index.column());
	case Qt::EditRole :
		return item->editData(index.column());
	default :
		return QVariant();
	}

	return QVariant();
}

bool Model::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (!index.isValid())
		return false;

	if (role != Qt::EditRole)
		return false;

	BrickModel *item = static_cast<BrickModel*>(index.internalPointer());

	return item->setData(index.column(), value);
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant Model::headerData(int section, Qt::Orientation orientation,
	int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return rootItem->data(section);

	return QVariant();
}

void Model::paintAll()
{
	foreach(BrickModel * bm, self().rootItem->children())
	{
		Renderer * rnd = reinterpret_cast<Renderer*>(bm);
		if(rnd)
			rnd->paint();
	}
}
