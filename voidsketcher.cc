/*
 * voidsketcher.cc
 *
 *  Created on: 5 nov 2018
 *      Author: erik
 */

#include "voidsketcher.h"

VoidSketcher::VoidSketcher(PaintBox *pb)
: GeometryObject(pb)
{
}

void VoidSketcher::sketch(xmlNode *node)
{
	GeometryObject::sketch(node);
	paintbox->move(x * length, y * length);
}
