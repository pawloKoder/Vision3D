#ifndef COLORLISTDELEGATE_H
#define COLORLISTDELEGATE_H

#include "basedelegate.h"

class ColorListDelegate : public BaseDelegate
{
public:
	ColorListDelegate();
	~ColorListDelegate();

	virtual bool canConvert(const QVariant &);

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
};

#endif // COLORLISTDELEGATE_H
