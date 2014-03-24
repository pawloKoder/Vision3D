#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <QVector3D>
#include <QVector>
#include <QString>

#include "../mesh/savefile.h"

class MeshLoader
{
public:
	struct Element{
		QVector3D nodes[8];
	};
	struct Wall{
		int nodes[4];
	};

	QVector<QVector3D> nodes;
	QVector<Element> elements;
	QVector<Wall> walls;

	int elementsNumber;
	int pointsNumber;

	explicit MeshLoader(QString = QString());
	void reload();

private:
	QString path;

	void appendWall(const Cube &,unsigned, unsigned, unsigned, unsigned);
};
#endif // MESHLOADER_H
