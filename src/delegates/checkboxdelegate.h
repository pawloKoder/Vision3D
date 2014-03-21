#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include "basedelegate.h"

class CheckBoxDelegate : public BaseDelegate
{
public:
	CheckBoxDelegate();

	virtual bool canConvert(const QVariant &);

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
};

#endif // CHECKBOXDELEGATE_H
