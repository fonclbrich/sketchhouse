/*
 * voidsketcher.h
 *
 *  Created on: 5 nov 2018
 *      Author: erik
 */

#ifndef VOIDSKETCHER_H_
#define VOIDSKETCHER_H_

#include "geometryobject.h"

class VoidSketcher : public GeometryObject
{
public:
	VoidSketcher(PaintBox *pb);
	virtual void sketch(xmlNode *node);
};


#endif /* VOIDSKETCHER_H_ */
