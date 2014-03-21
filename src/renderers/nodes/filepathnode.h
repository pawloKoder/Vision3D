#ifndef FILEPATHNODE_H
#define FILEPATHNODE_H

#include "node.h"
#include "../../base/filepath.h"

class FilePathNode : public Node<FilePath>
{
public:
	FilePathNode(BrickModel* parent, FilePath value = FilePath(), QString description = QString());

	virtual QVariant data(int column) const;
};

#endif // FILEPATHNODE_H
