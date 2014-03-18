#ifndef PATHNODE_H
#define PATHNODE_H

#include "../brickmodel.h"

class PathNode : public BrickModel
{
public:
	PathNode(BrickModel* parent, QString value = QString(), QString description = QString());
	virtual ~PathNode();

	void setPath(QString);
	QString path() const;
};

#endif // PATHNODE_H
