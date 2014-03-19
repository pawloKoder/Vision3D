#ifndef COLORNODE_H
#define COLORNODE_H

#include <QColor>

#include "node.h"

class ColorNode : public Node<QColor>
{
public:
	ColorNode(BrickModel* parent, QColor value = QColor(), QString description = "Color");
	virtual ~ColorNode();

	virtual QVariant decorationData(int column) const;
};


#endif // COLORNODE_H
