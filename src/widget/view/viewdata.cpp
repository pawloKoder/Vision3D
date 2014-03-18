#include "viewdata.h"

ViewData::ViewData() :
	zoom(1.0)
{
	for(int i=0; i<3; ++i)
		rotation[i] = 0.0;
}
