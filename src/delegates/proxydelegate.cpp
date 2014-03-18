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
	foreach(BaseDelegate * delegete, delegates)
		if(delegete->canConvert(index.data()))
			return delegete->createEditor(parent, option, index);

	return QItemDelegate::createEditor(parent, option, index);
}

void ProxyDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	foreach(BaseDelegate * delegete, delegates)
		if(delegete->canConvert(index.data())) {
			delegete->setEditorData(editor, index);
			return;
		}

	QItemDelegate::setEditorData(editor, index);
}

void ProxyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	foreach(BaseDelegate * delegete, delegates)
		if(delegete->canConvert(index.data())) {
			delegete->setModelData(editor, model, index);
			return;
		}

	QItemDelegate::setModelData(editor, model, index);
}


void ProxyDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex & index ) const
{
	foreach(BaseDelegate * delegete, delegates)
		if(delegete->canConvert(index.data())) {
			delegete->updateEditorGeometry(editor, option, index);
			return;
		}

	QItemDelegate::updateEditorGeometry(editor, option, index);
}
