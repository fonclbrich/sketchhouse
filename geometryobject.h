/*
 * geometryobject.h
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */

#ifndef GEOMETRYOBJECT_H_
#define GEOMETRYOBJECT_H_


#include "delegatesketcher.h"

class GeometryObject : public DelegateSketcher
{
private:
	void translateDirection(xmlNode *node);
	void translateLength(xmlNode *node);
	void translateWidth(xmlNode *node);

protected:
	double x;
	double y;

	double length;
	double width;

public:
	GeometryObject(PaintBox *pb);
};


#endif /* GEOMETRYOBJECT_H_ */
