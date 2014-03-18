#include "filepath.h"

FilePath::FilePath(QString p) :
	path(p)
{

}

QString FilePath::getString() const
{
	return path;
}

void FilePath::set(QString p)
{
	path = p;
}

FilePath::operator QString() const
{
	return "LOL";
	return getString();
}
