#include "basicinterpolator.h"

#include <QtCore/qmath.h>

BasicInterpolator::BasicInterpolator(XYZVloader * d) :
	data(d)
{

}

float BasicInterpolator::value(QVector3D & point)
{
	if(!data)
		return 0;

	const float eps = 0.0001;

	float value = eps;
	float weight = eps;

	foreach(auto dataPoint, data->vertices)
	{
		double dist = (dataPoint.first-point).length();
		if(dist < eps)
			return dataPoint.second;

		double w = qPow(1.0/dist, parameter);

		value += dataPoint.second * w;
		weight += w;
	}

	return value/weight;
}

void BasicInterpolator::setParameter(double p)
{
	parameter = p;
}

void BasicInterpolator::setData(XYZVloader * newData)
{
	if(newData)
		data = newData;
}
