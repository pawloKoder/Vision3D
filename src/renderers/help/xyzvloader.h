#ifndef XYZVLOADER_H
#define XYZVLOADER_H

#include <QPair>
#include <QVector>
#include <QVector3D>
#include <QString>

class XYZVloader
{
	struct Less
	{
		bool operator()(const QPair<QVector3D, double> & a,
			const QPair<QVector3D, double> & b) const
		{
			return a.second < b.second;
		}
	};

public:
	float min[4];
	float max[4];
	QVector<QPair<QVector3D, double>> vertices;

	explicit XYZVloader(QString = QString());
	void reload();
	void sortByValues();

private:
	QString path;
};

#endif // XYZVLOADER_H
