#ifndef COLORNODE_H
#define COLORNODE_H

#include <QColor>

#include "../brickmodel.h"

class ColorNode : public BrickModel
{
public:
	ColorNode(BrickModel* parent, QColor value = QColor(), QString description = "Color");
	virtual ~ColorNode();

	void setColor(QColor);
	QColor color() const;

	virtual QVariant decorationData(int column) const;
};


#endif // COLORNODE_H
