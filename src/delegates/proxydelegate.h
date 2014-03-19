#ifndef DELEGATE_H
#define DELEGATE_H

#include <QItemDelegate>

#include "basedelegate.h"

class ProxyDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	ProxyDelegate(QWidget *parent = nullptr);

	void registerDelegate(BaseDelegate*);

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	virtual void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

private:
	QList<BaseDelegate*> delegates;

	BaseDelegate * getDelegate(const QModelIndex &) const;
};
#endif // DELEGATE_H
