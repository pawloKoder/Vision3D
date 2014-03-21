#ifndef NODE_H
#define NODE_H

#include "../brickmodel.h"

template<class T>
class Node : public BrickModel
{
public:
	Node(BrickModel* parent, T value = T(), QString description = QString());
	virtual ~Node();

	virtual QVariant data(int column) const;

	void setValue(T);
	T getValue() const;
};

#include "node.cpp"

#endif // NODE_H
