#include "isosurfacerenderer.h"

#include <QDebug>
#include <QVector3D>
#include <GL/glu.h>

IsosurfaceRenderer::IsosurfaceRenderer()
{
	level = new Node<double>(this, 0.1, "ValueOfIsosurface");
	bisearchLevel = new Node<int>(this, 5, "Level of bisearch algorithm");
	elementSize = 0.04;

	for(int i = 0; i < 3; ++i)
	{
		numOfElements[i] = 50;
		begin[i] = -1.0;
	}

}

IsosurfaceRenderer::~IsosurfaceRenderer()
{
}

QString IsosurfaceRenderer::getName() const
{
	return "Isosurface";
}

QString IsosurfaceRenderer::getDesc() const
{
	return "Isosurface renderer";
}

void IsosurfaceRenderer::paintImpl()
{
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);

	 GLfloat ambientLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat specLightColor[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos[] = {7 , 7 , 7 , 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specLightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	float specularity = 0.45;
	float emissivity = 0.00f;
	float shininess = 60;

	GLfloat materialSpecular[] = {specularity, specularity, specularity, 1.0f};
	GLfloat materialEmission[] = {emissivity, emissivity, emissivity, 1.0f};

	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	marchingTetrahedrons();

	glDisable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
}

void IsosurfaceRenderer::marchingTetrahedrons()
{
	updateSettings();

	float diff[8][3];
	for(int i=0; i<8; ++i)
		for(int j=0; j<3; ++j)
			diff[i][j] = elementSize * (i&(1<<j) ? 0.0 : -1.0);

	glPushMatrix();

	float cords[3];
	int nums[3];

	float cube[8][3];
	QVector3Dext nodes[8];

	numOfNodes =  numOfElements[0]* numOfElements[1]* numOfElements[2];
	normals.clear();

	for(nums[0] = 1; nums[0] < numOfElements[0]; ++nums[0])
	{
		for(nums[1] = 1; nums[1] < numOfElements[1]; ++nums[1])
			for(nums[2] = 1; nums[2] < numOfElements[2]; ++nums[2])
			{
				for(int j=0; j<3; ++j)
					cords[j] = begin[j] + elementSize*nums[j];

				for(int i=0; i<8; ++i)
					for(int j=0; j<3; ++j)
						cube[i][j] = cords[j] + diff[i][j];

				for(int i=0; i<8; ++i)
				{
					nodes[i].pos.setX(cube[i][0]);
					nodes[i].pos.setY(cube[i][1]);
					nodes[i].pos.setZ(cube[i][2]);
					nodes[i].num = 1;
					nodes[i].num += numOfElements[2] * numOfElements[1] *  (nums[0] + (i&1 ? 1 : 0));
					nodes[i].num += numOfElements[2] * (nums[1] + (i&2 ? 1 : 0));
					nodes[i].num += nums[2] + (i&4 ? 1 : 0);
				}

				computeTetrahedon(nodes[3],nodes[6],nodes[2],nodes[1]);
				computeTetrahedon(nodes[0],nodes[6],nodes[1],nodes[2]);
				computeTetrahedon(nodes[7],nodes[1],nodes[6],nodes[3]);
				computeTetrahedon(nodes[0],nodes[1],nodes[6],nodes[4]);
				computeTetrahedon(nodes[1],nodes[4],nodes[5],nodes[6]);
				computeTetrahedon(nodes[1],nodes[6],nodes[5],nodes[7]);
			}
	}

	drawTriangles();
	glPopMatrix();
}


void IsosurfaceRenderer::updateSettings()
{
	if(cachePath != path->getValue().getString())
	{
		cachePath = path->getValue().getString();
		data = XYZVloader(cachePath);
	}
}

void IsosurfaceRenderer::computeTetrahedon(QVector3Dext & a, QVector3Dext & b, QVector3Dext & c, QVector3Dext &d)
{
	int flag = 0;
	if(test(a.pos))flag |= 0b1000;
	if(test(b.pos))flag |= 0b0100;
	if(test(c.pos))flag |= 0b0010;
	if(test(d.pos))flag |= 0b0001;

	switch(flag)
	{
		case 0b0001 :
			oneInv(d,a,b,c);
		break;
		case 0b1110 :
			one(d,a,b,c);
		break;

		case 0b0010 :
			oneInv(c,b,a,d);
		break;
		case 0b1101 :
			one(c,b,a,d);
		break;

		case 0b0100 :
			oneInv(b,a,c,d);
		break;
		case 0b1011 :
			one(b,a,c,d);
		break;

		case 0b1000 :
			oneInv(a,c,b,d);
		break;
		case 0b0111 :
			one(a,c,b,d);
		break;

		case 0b1100 :
			two(c,d, a,b);
		break;
		case 0b0011 :
			two(a,b,c,d);
		break;

		case 0b1010 :
			two(b, d, c, a);
		break;
		case 0b0101 :
			two(c,a,b,d);
		break;

		case 0b1001 :
			two(b,c, a,d);
		break;
		case 0b0110 :
			two(a,d,b,c);
		break;
		default:
		break;
	}
}

void IsosurfaceRenderer::one(QVector3Dext & a, QVector3Dext & b , QVector3Dext & c , QVector3Dext & d)
{
	Triangle tr;
	float r = test(a.pos, b.pos);
	tr.cords[0].pos = a.pos*r + b.pos*(1.0-r);
	tr.cords[0].num = std::min(a.num,b.num) * numOfNodes + std::max(a.num,b.num);

	r = test(a.pos, c.pos);
	tr.cords[1].pos = a.pos*r + c.pos*(1.0-r);
	tr.cords[1].num = std::min(a.num,c.num) * numOfNodes + std::max(a.num,c.num);

	r = test(a.pos, d.pos);
	tr.cords[2].pos = a.pos*r + d.pos*(1.0-r);
	tr.cords[2].num = std::min(a.num,d.num) * numOfNodes + std::max(a.num,d.num);

	triangles.push_back(tr);

	QVector3D norm = QVector3D::crossProduct(tr.cords[0].pos- tr.cords[2].pos, tr.cords[1].pos-tr.cords[2].pos).normalized();
	normals[tr.cords[0].num] += norm;
	normals[tr.cords[1].num] += norm;
	normals[tr.cords[2].num] += norm;
}

void IsosurfaceRenderer::oneInv(QVector3Dext & a, QVector3Dext & b , QVector3Dext & c , QVector3Dext & d)
{
	Triangle tr;
	float r = test(a.pos, b.pos);
	tr.cords[0].pos = a.pos*r + b.pos*(1.0-r);
	tr.cords[0].num = std::min(a.num,b.num) * numOfNodes + std::max(a.num,b.num);

	r = test(a.pos, c.pos);
	tr.cords[2].pos = a.pos*r + c.pos*(1.0-r);
	tr.cords[2].num = std::min(a.num,c.num) * numOfNodes + std::max(a.num,c.num);

	r = test(a.pos, d.pos);
	tr.cords[1].pos = a.pos*r + d.pos*(1.0-r);
	tr.cords[1].num = std::min(a.num,d.num) * numOfNodes + std::max(a.num,d.num);

	triangles.push_back(tr);

	QVector3D norm = QVector3D::crossProduct(tr.cords[0].pos- tr.cords[2].pos, tr.cords[1].pos-tr.cords[2].pos).normalized();
	normals[tr.cords[0].num] += norm;
	normals[tr.cords[1].num] += norm;
	normals[tr.cords[2].num] += norm;
}

void IsosurfaceRenderer::two(QVector3Dext &a, QVector3Dext &b, QVector3Dext & c, QVector3Dext & d)
{
	QVector3Dext cords[4];

	float r = test(a.pos, c.pos);
	cords[0].pos = a.pos*r+c.pos*(1.0-r);
	cords[0].num = std::min(a.num,c.num) * numOfNodes + std::max(a.num,c.num);

	r = test(a.pos, d.pos);
	cords[1].pos = a.pos*r+d.pos*(1.0-r);
	cords[1].num = std::min(a.num,d.num) * numOfNodes + std::max(a.num,d.num);

	r = test(b.pos, c.pos);
	cords[2].pos = b.pos*r+c.pos*(1.0-r);
	cords[2].num = std::min(b.num,c.num) * numOfNodes + std::max(b.num,c.num);

	r = test(b.pos, d.pos);
	cords[3].pos = b.pos*r+d.pos*(1.0-r);
	cords[3].num = std::min(b.num,d.num) * numOfNodes + std::max(b.num,d.num);

	Triangle tr;

	tr.cords[0] = cords[0];
	tr.cords[1] = cords[2];
	tr.cords[2] = cords[1];
	triangles.push_back(tr);

	QVector3D norm = QVector3D::crossProduct(tr.cords[0].pos- tr.cords[2].pos, tr.cords[1].pos-tr.cords[2].pos).normalized();

	normals[tr.cords[0].num] += norm;
	normals[tr.cords[1].num] += norm;
	normals[tr.cords[2].num] += norm;

	tr.cords[0] = cords[1];
	tr.cords[1] = cords[2];
	tr.cords[2] = cords[3];
	triangles.push_back(tr);

	norm = QVector3D::crossProduct(tr.cords[0].pos- tr.cords[2].pos, tr.cords[1].pos-tr.cords[2].pos).normalized();

	normals[tr.cords[0].num] += norm;
	normals[tr.cords[1].num] += norm;
	normals[tr.cords[2].num] += norm;
}

void IsosurfaceRenderer::drawTriangles()
{
	QColor c = rainbow.getColor(level->getValue());
	GLfloat materialColor[] = {(float)c.redF(), (float)c.greenF(), (float)c.blueF(), 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

	while(!triangles.empty())
	{
		Triangle tr = triangles.back();
		glBegin(GL_TRIANGLES);
		for(int i=0; i<3; ++i)
		{
			QVector3D norm = normals[tr.cords[i].num].normalized();
			glNormal3f(norm.x(), norm.y(), norm.z());
			glVertex3f(tr.cords[i].pos.x(), tr.cords[i].pos.y(), tr.cords[i].pos.z());
		}

		glEnd();
		triangles.pop_back();
	}
}

bool IsosurfaceRenderer::test(QVector3D & f)
{
	return f.length() < level->getValue();
}

float IsosurfaceRenderer::test(QVector3D & a, QVector3D & b)
{
	float left = 0;
	float right = 1.0;
	int stepNumber = bisearchLevel->getValue();

	if(!test(a))
		std::swap(left, right);

	for (int step = 0; step < stepNumber; ++step) {
		float middle = (left + right) / 2;

		QVector3D testPoint = a * middle + b * (1.0 - middle);
		if (test(testPoint) )
			right = middle;
		else
			left = middle;
	}

	return left;
}
