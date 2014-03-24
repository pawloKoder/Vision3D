#include "meshloader.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "../../base/strings.h"

/*					      ____________________  ___
						/|                  /|   |
					   / |		           / |   |
					  /	 |	    1         /  |   |
					 /	 |	             /   |   |LZ
					/____|______________/    |   |
					|	 |				|    |   |
					| 2  |  			| 3  |   |
					|	 |5_____________|____|  _|_
					|	 /				|    /   /
					|	/	            |   /   /
					|  /		0		|  /   / LY
					| / 				| /   /
					|/4_________________|/  _/_
							  LX
					|-------------------|
					0,1 - bottom, top surface
					2,3 - left, right surface
					4,5 - front, back surface
					LX - length along X
					LY - length along Y
					LZ - length along Z
					0 of the Cartesian coordinate system is the intersection of the 0,2,4 boundary surfaces
						 6___________________7  ___
						/|                  /|   |
					   / |                 / |   |
					  /  |                /  |   |
					 /   |               /   |   |LZ
					/4___|_____________5/    |   |
					|    |              |    |   |
					|    |              |    |   |
					|    |2_____________|___3|  _|_
					|    /              |    /   /
					|   /               |   /   /
					|  /                |  /   / LY
					| /                 | /   /
					|/0________________1|/  _/_
							  LX
					|-------------------|

					*/

MeshLoader::MeshLoader(QString p) :
	path(p)
{
	if(!path.isEmpty())
		reload();
}

void MeshLoader::reload()
{
	nodes.clear();
	elements.clear();
	walls.clear();

	try
	{
		LoadFile * load = new LoadFile(path.toStdString());
		elementsNumber = load->getElementsNumber();
		pointsNumber = load->getPointsNumber();

		while(load->isNextPoint())
		{
			serializedPoint p = load->getNextPoint();
			nodes.append(QVector3D(p.coordinate[0], p.coordinate[1], p.coordinate[2]));
		}

		while(load->isNextElement())
		{
			Cube cube(load->getNextElement());
			Element e;
			for(int i = 0; i < 8; i++)
				e.nodes[i] = nodes[cube.getNumberOfNode(i)];

			if(cube.isBoundaryWall(0))
				appendWall(cube, 0, 1, 3, 2);
			if(cube.isBoundaryWall(1))
				appendWall(cube, 4, 5, 7, 6);
			if(cube.isBoundaryWall(2))
				appendWall(cube, 0, 2, 6, 4);
			if(cube.isBoundaryWall(3))
				appendWall(cube, 1, 3, 7, 5);
			if(cube.isBoundaryWall(4))
				appendWall(cube, 0, 1, 5, 4);
			if(cube.isBoundaryWall(5))
				appendWall(cube, 2, 3, 7, 6);
		}
	}
	catch (std::string s)
	{
		QMessageBox::information(0, Strings::ErrorOpenFile, QString::fromStdString(s));
		throw s;
	}
}

void MeshLoader::appendWall(const Cube & cube,unsigned n1, unsigned n2, unsigned n3, unsigned n4)
{
	Wall w;
	w.nodes[0] = cube.getNumberOfNode(n1);
	w.nodes[1] = cube.getNumberOfNode(n2);
	w.nodes[2] = cube.getNumberOfNode(n3);
	w.nodes[3] = cube.getNumberOfNode(n4);

	walls.append(w);
}
