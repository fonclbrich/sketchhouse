/*
 * wallsketcher.cc
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */



#include "wallsketcher.h"
#include <iostream>

WallSketcher::WallSketcher(PaintBox *pb)
	: GeometryObject(pb)
{
}

void WallSketcher::sketch(xmlNode *node)
{
	GeometryObject::sketch(node);

	paintbox->move(x * length, y * length);
}

void WallSketcher::publish()
{
	cairo_rel_line_to(paintbox->top(), x * length, y * length);
}

Coordinates WallSketcher::traceback(cairo_t *outline, Coordinates forward, PieceList::iterator piece, PieceList::iterator passed)
{
	Coordinates c = {-y * width, x * width};

	publish();

	if (++piece != passed)
	{
		Coordinates backward = (*piece)->traceback(outline, c, piece, passed);
		cairo_rel_line_to(outline, forward.x - backward.x - x * length, forward.y - backward.y - y * length);
	}
	else
	{
		cairo_rel_line_to(outline, c.x, c.y);
		cairo_rel_line_to(outline, forward.x - x * length, forward.y - y * length);
	}

	return c;
}
