/*
 * stdroom.h
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */

#ifndef ROOMSKETCHER_H_
#define ROOMSKETCHER_H_

#include "delegatesketcher.h"
#include "geometrysketcher.h"

class RoomSketcher : public DelegateSketcher
{
private:
	GeometrySketcher *geometry;

	void doGeometry(xmlNode *node);

public:
	RoomSketcher(PaintBox *);
	virtual ~RoomSketcher();
};


#endif /* ROOMSKETCHER_H_ */
