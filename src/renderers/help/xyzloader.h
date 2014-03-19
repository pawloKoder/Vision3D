#ifndef XYZLOADER_H
#define XYZLOADER_H

#include <QString>
#include <QVector>
#include <QVector3D>

class XYZloader
{
public:
	float min[3];
	float max[3];
	QVector<QVector3D> vertices;

	explicit XYZloader(QString = QString());
	void reload();

private:
	QString path;
};

#endif // XYZLOADER_H
