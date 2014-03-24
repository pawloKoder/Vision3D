#include "rainbow.h"

Rainbow::Rainbow()
{
}

QColor Rainbow::getColor(float value)
{
	const int stepNum = 7;
	float steps[stepNum][4] ={{0.00, 1.00, 0.00, 0.00},
						{0.16, 1.00, 0.49, 0.00},
						{0.32, 1.00, 1.00, 0.00},
						{0.48, 0.00, 1.00, 0.00},
						{0.64, 0.00, 0.00, 1.00},
						{0.80, 0.44, 0.00, 1.00},
						{1.01, 0.56, 0.00, 1.00}};

	for(int i=1; i<stepNum; ++i)
		if(value < steps[i][0])
		{
			float tmp = (value - steps[i-1][0]) / (steps[i][0] - steps[i-1][0]);
			float r = steps[i][1] * tmp + steps[i-1][1] * (1.0 - tmp);
			float g = steps[i][2] * tmp + steps[i-1][2] * (1.0 - tmp);
			float b = steps[i][3] * tmp + steps[i-1][3] * (1.0 - tmp);
			QColor c;
			c.setRedF(r);
			c.setGreenF(g);
			c.setBlueF(b);
			return c;
		}
	return QColor();
}
