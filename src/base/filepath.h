#ifndef FILEPATH_H
#define FILEPATH_H

#include <QString>
#include <QVariant>

#include "../renderers/nodes/node.h"

class FilePath
{
public:
	FilePath(QString = QString());

	QString getString() const;
	void set(QString);

private:
	QString path;
};

Q_DECLARE_METATYPE(FilePath)

#endif // FILEPATH_H

