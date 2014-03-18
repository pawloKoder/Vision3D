#include "viewsettings.h"

ViewSettings::ViewSettings()
{
}

ViewSettings & ViewSettings::self()
{
	static ViewSettings instance;
	return instance;
}

void ViewSettings::setRotationX(int param)
{
	data.rotation[0] = 0.01*param;
	emit setViewData(data);
}

void ViewSettings::setRotationY(int param)
{
	data.rotation[1] = 0.01*param;
	emit setViewData(data);
}

void ViewSettings::setRotationZ(int param)
{
	data.rotation[2] = 0.01*param;
	emit setViewData(data);
}

void ViewSettings::setZoom(int param)
{
	data.zoom = 0.01*param;
	emit setViewData(data);
}

void ViewSettings::mouseMove(QPoint param)
{
	data.rotation[0] += -0.001*param.y();
	data.rotation[1] += 0.001*param.x();
	emit setViewData(data);
}

void ViewSettings::wheelDelta(int delta)
{
	data.zoom = qMin(1.0,qMax(0.0,data.zoom+0.0001*delta));
	emit setViewData(data);
}

ViewData ViewSettings::getViewData()
{
	return self().data;
}
