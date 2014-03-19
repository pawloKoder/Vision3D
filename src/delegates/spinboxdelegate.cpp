#include "spinboxdelegate.h"

#include <QSpinBox>

SpinBoxDelegate::SpinBoxDelegate()
{
}

bool SpinBoxDelegate::canConvert(const QVariant & variant)
{
	return variant.canConvert<int>();
}

QWidget * SpinBoxDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &/* option */,
	const QModelIndex &/* index */) const
{
	QSpinBox *editor = new QSpinBox(parent);
	editor->setMinimum(0);
	editor->setMaximum(100);

	return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	int value = index.model()->data(index, Qt::EditRole).toInt();

	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->interpretText();
	model->setData(index, spinBox->value(), Qt::EditRole);
}
