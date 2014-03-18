#include "pathdelegate.h"

#include <QVariant>
#include <QSpinBox>
#include <QDebug>

#include "../base/filepath.h"
#include "../widget/filepicker.h"

PathDelegate::PathDelegate()
{
}

bool PathDelegate::canConvert(const QVariant & variant)
{
	return variant.canConvert<FilePath>();
}

QWidget * PathDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &/* option */,
	const QModelIndex &/* index */) const
{
	return new FilePicker(parent);
}

void PathDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();

	FilePicker *picker = static_cast<FilePicker*>(editor);
	picker->set(value);
}

void PathDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	FilePicker *picker = static_cast<FilePicker*>(editor);
	model->setData(index,
		QVariant::fromValue(FilePath(picker->value())),
		Qt::EditRole);
}

