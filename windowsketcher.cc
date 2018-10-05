/*
 * windowsketcher.cc
 *
 *  Created on: 3 okt 2018
 *      Author: erik
 */



#include "windowsketcher.h"

WindowSketcher::WindowSketcher(PaintBox *pb)
 : GeometryObject(pb)
{

}

void WindowSketcher::sketch(xmlNode *node)
{
	GeometryObject::sketch(node);

	paintbox->move(x * length, y * length);
}
