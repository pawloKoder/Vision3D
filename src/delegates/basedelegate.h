#ifndef BASEDELEGATE_H
#define BASEDELEGATE_H

#include <QVariant>
#include <QItemDelegate>

class BaseDelegate : public QItemDelegate
{
public:
	BaseDelegate();

	virtual bool canConvert(const QVariant &) = 0;

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const = 0;
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const = 0;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const = 0;
	virtual void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex & index ) const;
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
};

#endif // BASEDELEGATE_H
