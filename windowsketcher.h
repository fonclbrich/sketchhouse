/*
 * windowsketcher.h
 *
 *  Created on: 3 okt 2018
 *      Author: erik
 */

#ifndef WINDOWSKETCHER_H_
#define WINDOWSKETCHER_H_


#include "geometryobject.h"

class WindowSketcher : public GeometryObject
{
public:
	WindowSketcher(PaintBox *pb);
	virtual void sketch(xmlNode *node);
};


#endif /* WINDOWSKETCHER_H_ */
