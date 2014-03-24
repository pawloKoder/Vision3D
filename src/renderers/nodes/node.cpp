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
QVariant Node<T>::data(int column) const
{
	return itemData.value(column);
}

template<class T>
void Node<T>::setValue(T value)
{
	itemData[0] = QVariant::fromValue(value);

	if(parent() != nullptr)
		parent()->childChanged();
}

template<class T>
T Node<T>::getValue() const
{
	return itemData[0].value<T>();
}
