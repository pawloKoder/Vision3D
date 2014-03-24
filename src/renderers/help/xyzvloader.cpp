#include "xyzvloader.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "../../base/strings.h"

XYZVloader::XYZVloader(QString p) :
	path(p)
{
	if(!path.isEmpty())
		reload();
}

void XYZVloader::reload()
{
	QFile file(path);

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(0, Strings::ErrorOpenFile, file.errorString());
		return;
	}

	vertices.clear();


	QTextStream in(&file);
	float values[4];
	bool first = true;

	while (!in.atEnd())
	{
		in >> values[0];
		in >> values[1];
		in >> values[2];
		in >> values[3];

		if (in.atEnd()) break;

		vertices.push_back(QPair<QVector3D, double>(QVector3D(values[0], values[1], values[2]),
			values[3]));

		if (first)
		{
			for (int i = 0; i < 4; ++i)
				min[i] = max[i] =  values[i];
			first = false;
		}
		else
			for (int i = 0; i < 4; ++i)
			{
				min[i] = std::min(min[i], values[i]);
				max[i] = std::max(max[i], values[i]);
			}
	}
}

void XYZVloader::sortByValues()
{
	qSort(vertices.begin(), vertices.end(), Less());
}
