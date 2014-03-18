#ifndef PATHDELEGATE_H
#define PATHDELEGATE_H

#include "basedelegate.h"

class PathDelegate : public BaseDelegate
{
public:
	PathDelegate();

	virtual bool canConvert(const QVariant &);

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
};


#endif // PATHDELEGATE_H
