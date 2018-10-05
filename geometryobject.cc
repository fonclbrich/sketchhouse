/*
 * geometryobject.cc
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */



#include "geometryobject.h"

#include <iostream>

GeometryObject::GeometryObject(PaintBox *pb)
	: DelegateSketcher(pb)
{
	y = 0;
	x = 0;

	length = 0;
	width = 0;

	addDelegate("direction", (Delegate) &GeometryObject::translateDirection);
	addDelegate("length", (Delegate) &GeometryObject::translateLength);
	addDelegate("width", (Delegate) &GeometryObject::translateWidth);
}


void GeometryObject::translateDirection(xmlNode *node)
{
	// This should be simple text

	const xmlChar *dirStr = xmlNodeGetContent(node);

	if (0 == xmlStrncasecmp(dirStr, (const xmlChar *) "east", 0x10))
	{
		y = 0;
		x = 1;
		return;
	}

	if (0 == xmlStrncasecmp(dirStr, (const xmlChar *) "west", 0x10))
	{
		y = 0;
		x = -1;
		return;
	}

	if (0 == xmlStrncasecmp(dirStr, (const xmlChar *) "south", 0x10))
	{
		y = 1;
		x = 0;
		return;
	}

	if (0 == xmlStrncasecmp(dirStr, (const xmlChar *) "north", 0x10))
	{
		y = -1;
		x = 0;
		return;
	}
}

void GeometryObject::translateLength(xmlNode *node)
{
	length = strtod((const char *) xmlNodeGetContent(node), NULL);
}

void GeometryObject::translateWidth(xmlNode *node)
{
	width = strtod((const char *) xmlNodeGetContent(node), NULL);
}
