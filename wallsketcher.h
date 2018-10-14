/*
 * wallsketcher.h
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */

#ifndef WALLSKETCHER_H_
#define WALLSKETCHER_H_


#include "geometryobject.h"
#include "segments.h"

class WallSketcher : public GeometryObject
{
public:
	WallSketcher(PaintBox *pb);

	virtual void sketch(xmlNode *node);
	virtual void publish();

	virtual Coordinates traceback(Coordinates modify, PieceList::iterator piece, PieceList::iterator passed);
	virtual Coordinates tracebackP(Coordinates modify, PieceList::iterator piece, PieceList::iterator passed);
};


#endif /* WALLSKETCHER_H_ */
