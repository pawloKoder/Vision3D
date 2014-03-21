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
	glDisable(GL_DEPTH_TEST);

	GLUquadricObj *quadric;
	quadric = gluNewQuadric();

	glPushMatrix();
	/*glTranslatef(-(data.min[0]+data.max[0])/2,
				 -(data.min[1]+data.max[1])/2,
				 -(data.min[2]+data.max[2])/2);*/

	foreach(auto it, data.vertices)
	{
		glPushMatrix();

		glTranslatef(it.first.x(), it.first.y(), it.first.z());
		setColor((it.second - data.min[3]) / (data.max[3] - data.min[3]));

		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluSphere(quadric, .1, 18, 9);

		glPopMatrix();
	}

	gluDeleteQuadric(quadric);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void MIPrenderer::setColor(float ratio)
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
		if(ratio < steps[i][0])
		{
			float tmp = ratio / (steps[i][0] - steps[i-1][0]);
			float r = (steps[i][1] - steps[i-1][1]) * tmp + steps[i-1][1];
			float g = (steps[i][2] - steps[i-1][2]) * tmp + steps[i-1][2];
			float b = (steps[i][3] - steps[i-1][3]) * tmp + steps[i-1][3];
			glColor3f(r,g,b);
			return;
		}
	glColor3f(.0,.0,.0);
}

void MIPrenderer::updateSettings()
{
	if(cachePath != path->getValue().getString())
	{
		cachePath = path->getValue().getString();
		data = XYZVloader(cachePath);
		data.sortByValues();
	}
}
