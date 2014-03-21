#include "miprenderer.h"

#include <QDebug>
#include <QVector3D>
#include <GL/glu.h>

MIPrenderer::MIPrenderer()
{

}

MIPrenderer::~MIPrenderer()
{
}

QString MIPrenderer::getName() const
{
	return "MIP";
}

QString MIPrenderer::getDesc() const
{
	return "MIP renderer";
}

void MIPrenderer::paintImpl()
{
	updateSettings();

}

void MIPrenderer::updateSettings()
{
	if(cachePath != path->getValue().getString())
	{
		cachePath = path->getValue().getString();
		data = XYZVloader(cachePath);
	}
}
