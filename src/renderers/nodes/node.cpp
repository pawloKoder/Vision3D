#include "node.h"

#include<QVariant>

template<class T>
Node<T>::Node(BrickModel* parent, T value, QString description)
{
	itemData.append(QVariant::fromValue(value));
	itemData.append(description);

	parent->appendChild(this);
}

template<class T>
Node<T>::~Node()
{

}

template<class T>
void Node<T>::setValue(T value)
{
	itemData[0] = QVariant::fromValue(value);
}

template<class T>
T Node<T>::getValue() const
{
	return itemData[0].value<T>();
}
