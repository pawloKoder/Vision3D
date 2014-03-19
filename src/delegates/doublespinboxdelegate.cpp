#include "doublespinboxdelegate.h"

#include <QDoubleSpinBox>

DoubleSpinBoxDelegate::DoubleSpinBoxDelegate()
{
}

bool DoubleSpinBoxDelegate::canConvert(const QVariant & variant)
{
	return variant.type() == QVariant::Double;
}

QWidget * DoubleSpinBoxDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &/* option */,
	const QModelIndex &/* index */) const
{
	QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
	editor->setMinimum(0);
	editor->setMaximum(100);
	editor->setSingleStep(0.01);

	return editor;
}

void DoubleSpinBoxDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	double value = index.model()->data(index, Qt::EditRole).toDouble();

	QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
	spinBox->setValue(value);
}

void DoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
	spinBox->interpretText();
	model->setData(index, spinBox->value(), Qt::EditRole);
}

