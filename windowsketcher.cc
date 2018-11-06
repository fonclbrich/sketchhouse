/*
 * windowsketcher.cc
 *
 *  Created on: 3 okt 2018
 *      Author: erik
 */



#include "windowsketcher.h"

WindowSketcher::WindowSketcher(PaintBox *pb)
 : GeometryObject(pb), color(153, 204, 255)
{
	thickness = 4;
	displacement = 8;
}

void WindowSketcher::sketch(xmlNode *node)
{
	GeometryObject::sketch(node);

	const Coordinates &curpos = paintbox->getPosition();

	cairo_move_to(paintbox->top(), curpos.x + y * displacement, curpos.y - x * displacement);
	cairo_set_source_rgb(paintbox->top(), color.red(), color.green(), color.blue());
	cairo_set_line_width(paintbox->top(), thickness);
	cairo_rel_line_to(paintbox->top(), x * length, y * length);
	cairo_stroke(paintbox->top());

	paintbox->move(x * length, y * length);
}
