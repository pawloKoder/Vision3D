#ifndef XYZVLOADER_H
#define XYZVLOADER_H

#include <QPair>
#include <QVector>
#include <QVector3D>
#include <QString>

class XYZVloader
{
public:
	float min[4];
	float max[4];
	QVector<QPair<QVector3D, double>> vertices;

	explicit XYZVloader(QString = QString());
	void reload();

private:
	QString path;
};

#endif // XYZVLOADER_H
