#include "colorlistdelegate.h"

#include "../widget/colorlisteditor.h"

ColorListDelegate::ColorListDelegate()
{
}


ColorListDelegate::~ColorListDelegate()
{
}

bool ColorListDelegate::canConvert(const QVariant & variant)
{
	return variant.type() == QVariant::Color;
}

QWidget * ColorListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/,
	const QModelIndex &/*index*/) const
{
	return  new ColorListEditor(parent);
}

void ColorListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	ColorListEditor *picker = static_cast<ColorListEditor*>(editor);
	picker->setColor(index.model()->data(index, Qt::EditRole).value<QColor>());
}

void ColorListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	model->setData(index,
		static_cast<ColorListEditor*>(editor)->color(),
		Qt::EditRole);
}
