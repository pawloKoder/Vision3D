#ifndef DELEGATE_H
#define DELEGATE_H

#include <QItemDelegate>

#include "basedelegate.h"

class ProxyDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	ProxyDelegate(QWidget *parent = 0);

	void registerDelegate(BaseDelegate*);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex & index ) const;

private:
	QList<BaseDelegate*> delegates;
};
#endif // DELEGATE_H
