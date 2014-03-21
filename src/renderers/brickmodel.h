#ifndef BRICKMODEL_H
#define BRICKMODEL_H

#include <QMap>
#include <QVariant>

class BrickModel
{
public:
	BrickModel(const QList<QVariant> &data, BrickModel *parent = 0);
	BrickModel(BrickModel *parent = 0);
	virtual ~BrickModel();

	void appendChild(BrickModel *child);

	BrickModel *child(int row);
	const QList<BrickModel*> &children();
	int childCount() const;
	int columnCount() const;
	int row() const;

	virtual QVariant data(int column) const;
	virtual QVariant editData(int column) const;
	virtual QVariant decorationData(int column) const;
	virtual bool setData(int column, QVariant value);

	BrickModel *parent();

protected:
	QList<BrickModel*> childItems;
	QList<QVariant> itemData;
	BrickModel *parentItem;

private:
	void setParent(BrickModel *);
};

#endif // BRICKMODEL_H
