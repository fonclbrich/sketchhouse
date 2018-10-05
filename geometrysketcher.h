/*
 * geometrysketcher.h
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */

#ifndef GEOMETRYSKETCHER_H_
#define GEOMETRYSKETCHER_H_

#include "wallsketcher.h"

using namespace std;

class GeometrySketcher : public DelegateSketcher
{
private:
	BoundingBox *bb;
	PieceList wallPieces;

	bool didWall;

	virtual void prologue();

	Coordinates wallStart;

public:
	GeometrySketcher(PaintBox *pb);
	~GeometrySketcher();

	void doWall(xmlNode *node);
	void doWindow(xmlNode *node);
	void doAlign(xmlNode *node);

	virtual void sketch(xmlNode *node);
};

#endif /* GEOMETRYSKETCHER_H_ */
