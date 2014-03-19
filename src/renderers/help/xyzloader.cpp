#include "xyzloader.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "../../base/strings.h"

XYZloader::XYZloader(QString p) :
	path(p)
{
	if(!path.isEmpty())
		reload();
}

void XYZloader::reload()
{
	QFile file(path);

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(0, Strings::ErrorOpenFile, file.errorString());
		return;
	}

	vertices.clear();

	QTextStream in(&file);
	float values[3];

	while (!in.atEnd())
	{
		in >> values[0];
		in >> values[1];
		in >> values[2];

		if (in.atEnd()) break;

		vertices.push_back(QVector3D(values[0], values[1], values[2]));

		for (int i = 0; i < 3; ++i)
		{
			min[i] = std::min(min[i], values[i]);
			max[i] = std::max(max[i], values[i]);
		}
	}
}
