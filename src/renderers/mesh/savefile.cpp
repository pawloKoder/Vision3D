#include "savefile.h"

#include <cassert>
#include <cstring>
#include <exception>
#include <string>

void concentratedForces::clear()
{
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 3; ++j)
			values[i][j] = 0.0;
}

Cube::Cube(serializedQuadrilateral data)
{
	int transNodes[8];
	transNodes[0] = 0;
	transNodes[1] = 3;
	transNodes[2] = 1;
	transNodes[3] = 2;
	transNodes[4] = 4;
	transNodes[5] = 7;
	transNodes[6] = 5;
	transNodes[7] = 6;

	int trans[6];
	trans[0] = 4;
	trans[1] = 5;
	trans[2] = 0;
	trans[3] = 2;
	trans[4] = 3;
	trans[5] = 1;

	for(int i = 0; i < 8; ++i)
		nodes[i] = data.nodes[transNodes[i]];

	for(int i = 0; i < 6; ++i)
		connected[i]= data.connected[trans[i]];

	for(int j = 0; j < 3; ++j)
		for(int i = 0; i < 6; ++i)
			Q[i][j] = 0.0;

	for(int j = 0; j < 3; ++j)
		for(int i = 0; i < 6; ++i)
			if(trans[i] < i)
				Q[i][j]= data.Q[trans[i]][j];

	for(int i = 0; i < 4; ++i)
			P[i] = 0.0;
}

float Cube::getLoadX(unsigned wall)
{
	return Q[wall][0];
}

float Cube::getLoadY(unsigned wall)
{
	return Q[wall][1];
}

float Cube::getLoadZ(unsigned wall)
{
	return Q[wall][2];
}

float Cube::getPresure(unsigned wall)
{
	return P[wall];
}

bool Cube::isBoundaryWall(unsigned wall)
{
	return connected[wall] < 0;
}

unsigned Cube::getNumberOfNode(unsigned node) const
{
	return nodes[node];
}

static unsigned previousHeaderNum = 0x1EABA15D;
static unsigned previousHeaderNum2 = 0x1EABA15E;
static unsigned previousHeaderNum3 = 0x1EABA15F;
static unsigned headerNum = 0x1EABC15F;

void SaveFile::writeHelper(const char *data, unsigned size)
{
	if (file.sputn(data, size) != (int)size)
		throw std::string("Writing to file failed.");
}

SaveFile::SaveFile(std::string path)
{
	assert(sizeof(serializedPoint) == 24 && "ABI changed");
	assert(sizeof(serializedQuadrilateral) == 152 && "ABI changed");

	std::ios_base::openmode openmode = std::ios_base::binary | std::ios_base::out | std::ios_base::trunc;

	file.open(path.c_str(), openmode);
	if (!file.is_open())
		throw "Error opening file " + path;

	writeHelper(reinterpret_cast<const char *>(&headerNum),sizeof(unsigned));
}

void SaveFile::apply(serializedPoint & p)
{
	points.push_back(p);
}

void SaveFile::apply(serializedQuadrilateral & element)
{
	elements.push_back(element);
}

void SaveFile::saveAll()
{
	unsigned N = points.size();
	writeHelper(reinterpret_cast<const char *>(&N),sizeof(unsigned));
	unsigned M = elements.size();
	writeHelper(reinterpret_cast<const char *>(&M),sizeof(unsigned));

	writeHelper(reinterpret_cast<const char *>(&forces), sizeof(concentratedForces));

	for(unsigned i = 0; i< N; ++i){
		writeHelper(reinterpret_cast<const char *>(&points[i]), sizeof(serializedPoint));
	}

	for(unsigned i = 0; i< M; ++i){
		writeHelper(reinterpret_cast<const char *>(&elements[i]), sizeof(serializedQuadrilateral));
	}
}

SaveFile::~SaveFile()
{
	saveAll();
}

LoadFile::LoadFile(std::string path) :
	pointsIterator(0),
	elementsIterator(0)
{
	std::ios_base::openmode openmode = std::ios_base::binary | std::ios_base::in;;

	file.open(path.c_str(), openmode);
	if (!file.is_open())
		throw "Error opening file " + path;

	unsigned header;
	readHelper(reinterpret_cast<char *>(&header), sizeof(unsigned));

	if(header == previousHeaderNum)
		throw std::string("Thats not a correct mesh file. Propably previous version");

	if(header == previousHeaderNum2)
		loadLegacy0x1EABA15E();
	else if(header == headerNum)
		loadCurrent();
	else
		throw std::string("Thats not a correct mesh file.");

}

void LoadFile::loadLegacy0x1EABA15E()
{
	unsigned N;
	readHelper(reinterpret_cast<char *>(&N), sizeof(unsigned));
	unsigned M;
	readHelper(reinterpret_cast<char *>(&M), sizeof(unsigned));

	for(unsigned i = 0; i< N; ++i)
	{
		serializedPoint tmp;
		readHelper(reinterpret_cast<char *>(&tmp), sizeof(serializedPoint));
		points.push_back(tmp);
	}

	for(unsigned i = 0; i< M; ++i)
	{
		serializedQuadrilateral tmp;
		readHelper(reinterpret_cast<char *>(&tmp), sizeof(serializedQuadrilateral));
		elements.push_back(tmp);
	}

	forces.clear();
}

void LoadFile::loadCurrent()
{
	unsigned N;
	readHelper(reinterpret_cast<char *>(&N), sizeof(unsigned));
	unsigned M;
	readHelper(reinterpret_cast<char *>(&M), sizeof(unsigned));

	readHelper(reinterpret_cast<char *>(&forces), sizeof(concentratedForces));

	for(unsigned i = 0; i< N; ++i)
	{
		serializedPoint tmp;
		readHelper(reinterpret_cast<char *>(&tmp), sizeof(serializedPoint));
		points.push_back(tmp);
	}

	for(unsigned i = 0; i< M; ++i)
	{
		serializedQuadrilateral tmp;
		readHelper(reinterpret_cast<char *>(&tmp), sizeof(serializedQuadrilateral));
		elements.push_back(tmp);
	}
}

void LoadFile::readHelper(char *data, unsigned size)
{
	if (file.sgetn(data, size) != (int)size)
		throw std::string("Unexpected end of file.");
}

int LoadFile::getPointsNumber()
{
	return points.size();
}

int LoadFile::getElementsNumber()
{
	return elements.size();
}

int LoadFile::getFreedomTakenNumber()
{
	int result = 0;

	for(unsigned i = 0; i < points.size(); ++i)
		for(unsigned j = 0; j < 3; ++j)
			if(points[i].freedomTaken[j])
				result++;

	return result;
}

void LoadFile::resetPointsIterator()
{
	pointsIterator = 0;
}

bool LoadFile::isNextPoint()
{
	return points.size() > pointsIterator;
}

serializedPoint LoadFile::getNextPoint()
{
	if(!isNextPoint())
		throw std::string("LoadFile : out of range.");

	return points[pointsIterator++];
}

void LoadFile::resetElementIterator()
{
	elementsIterator = 0;
}

bool LoadFile::isNextElement()
{
	return elements.size() > elementsIterator;
}

serializedQuadrilateral LoadFile::getNextElement()
{
	if(!isNextElement())
		throw std::string("LoadFile : out of range.");

	return elements[elementsIterator++];
}
