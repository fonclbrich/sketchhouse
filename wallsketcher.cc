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
	cairo_rel_line_to(paintbox->bottom(), -y * width, x * width);
	cairo_rel_line_to(paintbox->middle(), -y * (width - 2), x * (width - 2));
}

Coordinates WallSketcher::traceback(Coordinates forward, PieceList::iterator piece, PieceList::iterator passed)
{
	Coordinates c(y * width, -x * width);

	cairo_rel_line_to(paintbox->top(), x * length, y * length);

	if (++piece != passed)
	{
		Coordinates backward = (*piece)->traceback(c, piece, passed);
		cairo_rel_line_to(paintbox->bottom(), forward.x - backward.x - x * length, forward.y - backward.y - y * length);
	}
	else
	{
		double X, Y;
		cairo_get_current_point(paintbox->top(), &X, &Y);

		cairo_move_to(paintbox->bottom(), X, Y);
		cairo_rel_line_to(paintbox->bottom(), c.x, c.y);
		cairo_rel_line_to(paintbox->bottom(), forward.x - x * length, forward.y - y * length);
	}

	return c;
}

Coordinates WallSketcher::tracebackP(Coordinates forward, PieceList::iterator piece, PieceList::iterator passed)
{
	Coordinates c(y * (width - 2), -x * (width - 2));

	cairo_rel_line_to(paintbox->middle(), x * length, y * length);

	if (++piece != passed)
	{
		Coordinates backward = (*piece)->tracebackP(c, piece, passed);
		cairo_rel_line_to(paintbox->middle(), forward.x - backward.x - x * length, forward.y - backward.y - y * length);
	}
	else
	{
		cairo_rel_line_to(paintbox->middle(), c.x, c.y);
		cairo_rel_line_to(paintbox->middle(), forward.x - x * length, forward.y - y * length);
	}

	return c;
}
