#include "filepathnode.h"

FilePathNode::FilePathNode(BrickModel* parent, FilePath value,
			 QString description) :
	Node<FilePath>(parent, value, description)
{

}

QVariant FilePathNode::data(int column) const
{
	if(column == 0)
		return Node<FilePath>::data(column).value<FilePath>().getString();

	return Node<FilePath>::data(column);
}
