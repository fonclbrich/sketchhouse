/*
 * stdroom.cc
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */

#include <iostream>

#include "roomsketcher.h"

RoomSketcher::RoomSketcher(PaintBox *pb)
 : DelegateSketcher(pb)
{
	geometry = new GeometrySketcher(pb);
	addDelegate("geometry", (Delegate) &RoomSketcher::doGeometry);
}

void RoomSketcher::doGeometry(xmlNode *node)
{
	geometry->sketch(node);
}

RoomSketcher::~RoomSketcher()
{
	delete geometry;
}
