#include "proxydelegate.h"

#include "basedelegate.h"

ProxyDelegate::ProxyDelegate(QWidget *parent) :
	QItemDelegate(parent)
{

}

void ProxyDelegate::registerDelegate(BaseDelegate * delegate)
{
	delegates.append(delegate);
}

QWidget *ProxyDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	BaseDelegate * delegete = getDelegate(index);

	if(delegete)
		return delegete->createEditor(parent, option, index);

	return QItemDelegate::createEditor(parent, option, index);
}

void ProxyDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	BaseDelegate * delegete = getDelegate(index);

	if(delegete)
		delegete->setEditorData(editor, index);
	else
		QItemDelegate::setEditorData(editor, index);
}

void ProxyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	BaseDelegate * delegete = getDelegate(index);

	if(delegete)
		delegete->setModelData(editor, model, index);
	else
		QItemDelegate::setModelData(editor, model, index);
}


void ProxyDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	BaseDelegate * delegete = getDelegate(index);

	if(delegete)
		delegete->updateEditorGeometry(editor, option, index);
	else
		QItemDelegate::updateEditorGeometry(editor, option, index);
}

void ProxyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	BaseDelegate * delegete = getDelegate(index);

	if(delegete)
		delegete->paint(painter, option, index);
	else
		QItemDelegate::paint(painter, option, index);
}

BaseDelegate * ProxyDelegate::getDelegate(const QModelIndex &index) const
{
	foreach(BaseDelegate * delegete, delegates)
		if(delegete->canConvert(index.data(Qt::EditRole)))
			return delegete;
	return nullptr;
}
