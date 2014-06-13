#pragma once

#include <fstream>
#include <vector>

struct serializedPoint
{
	float coordinate[3];
	//If freedomTaken is false point has freedom of move.
	int freedomTaken[3];
};

struct serializedQuadrilateral
{
	//Numbers of points. If its a 2D task nodes 4-7 are the same as 0-3.
	int nodes[8];
	// Cells connected to Quadrilateral.
	// connected[i]  quadrilateral borders to edge(nodes[i],nodes[i+1]).
	// If connected[i] < 0 edge(nodes[i],nodes[i+1]) is global border.
	// last two are top and bottom.
	int connected[6];

	// Q[i][j] means load on edge(nodes[i],nodes[i+1]) in x(0),y(1) direction.
	float Q[4][3];

	float normals[4][2];

	// Q[i][j] means preasure on edge(nodes[i],nodes[i+1]) in x(0),y(1) direction.
	float P[4];
};

struct concentratedForces
{
	void clear();

	float values[4][3];
};

class Cube
{
	float Q[6][3]; //Load on walls
	float P[6];

	int connected[6];

	unsigned nodes[8];

public:
	Cube(serializedQuadrilateral);

	float getLoadX(unsigned wall);
	float getLoadY(unsigned wall);
	float getLoadZ(unsigned wall);
	float getPresure(unsigned wall);

	bool isBoundaryWall(unsigned wall);

	unsigned getNumberOfNode(unsigned node) const;
};

class SaveFile
{
	std::filebuf file;

	std::vector<serializedPoint> points;
	std::vector<serializedQuadrilateral> elements;


	void writeHelper(const char *data, unsigned size);
	void saveAll();
public:
	concentratedForces forces;
	//! Opens file to save data.
	SaveFile(std::string path);

	void apply(serializedPoint &);
	void apply(serializedQuadrilateral &);

	//! Puts all data in file.
	~SaveFile();
};

class LoadFile
{
	std::filebuf file;

	unsigned pointsIterator;
	unsigned elementsIterator;

	void readHelper(char *data, unsigned size);

	void loadLegacy0x1EABA15E();
	void loadCurrent();
public:
	std::vector<serializedPoint> points;
	std::vector<serializedQuadrilateral> elements;
	concentratedForces forces;

	LoadFile(std::string path);

	int getPointsNumber();
	int getElementsNumber();
	int getFreedomTakenNumber();

	//! Revind points iterator to first point.
	void resetPointsIterator();
	//! True if there is a point to acces.
	bool isNextPoint();
	//! Returns point. If there is no points left, it raises a exception.
	serializedPoint getNextPoint();

	//! Revind points iterator to first element.
	void resetElementIterator();
	//! True if there is an element to acces.
	bool isNextElement();
	//! Returns element. If there is no elements left, it raises a exception.
	serializedQuadrilateral getNextElement();
};
