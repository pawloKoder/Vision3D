#include "checkboxdelegate.h"

#include <QCheckBox>

CheckBoxDelegate::CheckBoxDelegate()
{
}

bool CheckBoxDelegate::canConvert(const QVariant & variant)
{
	return variant.type() == QVariant::Bool;
}

QWidget * CheckBoxDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &/* option */,
	const QModelIndex &/* index */) const
{
	QCheckBox *editor = new QCheckBox(parent);
	return editor;
}

void CheckBoxDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	bool value = index.model()->data(index, Qt::EditRole).toBool();
	QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
	checkbox->setChecked(value);
}

void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
	model->setData(index, checkbox->isChecked(), Qt::EditRole);
}

