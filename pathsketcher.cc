/*
 * pathsketcher.cc
 *
 *  Created on: 13 okt 2018
 *      Author: erik
 */


#include "pathsketcher.h"

void Path::translateOrigin(xmlNode *node)
{
	orig = (const char *)xmlNodeGetContent(node);
}

void Path::translateDestination(xmlNode *node)
{
	dest = (const char *)xmlNodeGetContent(node);
}


Path::Path()
	: GeometryObject(NULL)
{
	addDelegate("origin", (Delegate) &Path::translateOrigin);
	addDelegate("destination", (Delegate) &Path::translateDestination);
}

const string &Path::origin()
{
	return orig;
}

const string &Path::destination()
{
	return dest;
}

const Coordinates Path::offset()
{
	return {length * x, length *y};
}
