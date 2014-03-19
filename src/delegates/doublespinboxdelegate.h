#ifndef DOUBLESPINBOXDELEGATE_H
#define DOUBLESPINBOXDELEGATE_H

#include "basedelegate.h"

class DoubleSpinBoxDelegate : public BaseDelegate
{
public:
	DoubleSpinBoxDelegate();

	virtual bool canConvert(const QVariant &);

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
};

#endif // DOUBLESPINBOXDELEGATE_H
