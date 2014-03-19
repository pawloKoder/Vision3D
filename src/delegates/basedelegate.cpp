#include "basedelegate.h"

BaseDelegate::BaseDelegate()
{
}

void BaseDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex & /*index*/) const
{
	editor->setGeometry(option.rect);
}

void BaseDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	QItemDelegate::paint(painter, option, index);
}
