#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>

class BrickModel;
class Renderer;

class Model : public QAbstractItemModel
{
	Q_OBJECT

	Model(QObject *parent = 0);
	virtual ~Model();

public:
	static Model & self();

	void createNewView(Renderer *);

	static void paintAll();

	virtual QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column,
		const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

private:
	BrickModel *rootItem;
};

#endif // MODEL_H
