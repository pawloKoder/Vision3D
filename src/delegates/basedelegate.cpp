#include "basedelegate.h"

BaseDelegate::BaseDelegate()
{
}

void BaseDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex & index ) const
{
	editor->setGeometry(option.rect);
}
