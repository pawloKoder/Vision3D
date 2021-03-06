#ifndef ISOSURFACERENDERER_H
#define ISOSURFACERENDERER_H

#include "renderer.h"
#include "help/xyzvloader.h"
#include "help/rainbow.h"
#include "help/basicinterpolator.h"
#include "nodes/colornode.h"
#include "nodes/node.h"

class IsosurfaceRenderer : public Renderer
{

	struct QVector3Dext
	{
		QVector3D pos;
		int num;
	};

	struct Triangle
	{
		QVector3Dext cords[3];
	};

	std::map<long long, QVector3D> normals;

public:
	IsosurfaceRenderer();
	virtual ~IsosurfaceRenderer();

	virtual QString getName() const;
	virtual QString getDesc() const;

protected:
	virtual void paintImpl();

private:
	double begin[3];
	int numOfElements[3];
	int numOfNodes;
	Rainbow rainbow;
	bool changed;
	BasicInterpolator interpolator;
	std::vector<Triangle> triangles;

	QString cachePath;
	XYZVloader data;

	Node<double> * level;
	Node<int> * bisearchLevel;
	Node<double> * elementSize;
	virtual void childChanged();

	void updateSettings();

	void marchingTetrahedrons();
	void drawTriangles();

	void computeTetrahedon(QVector3Dext &, QVector3Dext &, QVector3Dext &, QVector3Dext &);
	void one(QVector3Dext &, QVector3Dext &, QVector3Dext &, QVector3Dext &);
	void oneInv(QVector3Dext &, QVector3Dext &, QVector3Dext &, QVector3Dext &);
	void two(QVector3Dext &, QVector3Dext &, QVector3Dext &, QVector3Dext &);

	bool test(QVector3D &);
	float test(QVector3D &, QVector3D &);
};

#endif // ISOSURFACERENDERER_H
