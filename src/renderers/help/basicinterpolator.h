#ifndef BASICINTERPOLATOR_H
#define BASICINTERPOLATOR_H

#include <QVector3D>
#include "xyzvloader.h"

class BasicInterpolator
{
public:
	BasicInterpolator(XYZVloader * = nullptr);
	float value(QVector3D &);

	void setParameter(double);
	void setData(XYZVloader *);

private:
	XYZVloader * data;
	double parameter;
};

#endif // BASICINTERPOLATOR_H
