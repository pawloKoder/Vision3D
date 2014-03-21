#ifndef VIEWDATA_H
#define VIEWDATA_H

#include <QString>

class ViewData
{
public:
	float rotation[3];
	float zoom;

	bool projection;

	ViewData();
};

#endif // VIEWDATA_H
