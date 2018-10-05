/*
 * paintbox.cc
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */


#include "sketcher.h"
#include <cairo-ps.h>

PaintBox::PaintBox()
{

}

PaintBox::~PaintBox()
{

}

BoundingBox::BoundingBox(PaintBox *fb)
 : PaintBox()
{
	fallback = fb;

	boundingBox = cairo_ps_surface_create("debug.ps", 400, 400);
	bc = cairo_create(boundingBox);

	cairo_set_source_rgb(bc, 0, 0, 0);
	cairo_set_line_width(bc, 1);

	cairo_move_to(bc, 0, 0);
}

BoundingBox::~BoundingBox()
{
	cairo_destroy(bc);
	cairo_surface_finish(boundingBox);
	cairo_surface_destroy(boundingBox);
}

void BoundingBox::move(double dx, double dy)
{
	fallback->move(dx, dy);

	cairo_rel_line_to(bc, dx, dy);
}

const Coordinates &BoundingBox::getPosition()
{
	return fallback->getPosition();
}

void BoundingBox::done()
{
	cairo_close_path(bc);
	cairo_stroke_preserve(bc);
	cairo_fill(bc);

	cairo_surface_show_page(boundingBox);
}

void BoundingBox::maskback(Sketcher *s)
{

}

void BoundingBox::stamp(Alignment *a)
{
	fallback->stamp(a);
}


cairo_t *BoundingBox::top()
{
	return fallback->top();
}

cairo_t *BoundingBox::middle()
{
	return fallback->middle();
}

cairo_t *BoundingBox::bottom()
{
	return fallback->bottom();
}

Outliner::Outliner()
{
	segmentAdded = false;
	openSegment = NULL;

	/* topSurface = cairo_recording_surface_create(CAIRO_CONTENT_COLOR, NULL);
	middleSurface = cairo_recording_surface_create(CAIRO_CONTENT_COLOR, NULL);
	bottomSurface = cairo_recording_surface_create(CAIRO_CONTENT_COLOR, NULL); */

	topSurface = cairo_ps_surface_create("debugTop.ps", 800, 800);
	middleSurface = cairo_ps_surface_create("debugMiddle.ps", 800, 800);
	bottomSurface = cairo_ps_surface_create("debugBottom.ps", 800, 800);

	floatingTop = cairo_create(topSurface);
	floatingMiddle = cairo_create(middleSurface);
	floatingBottom = cairo_create(bottomSurface);

	cairo_set_source_rgb(floatingTop, 0, 0, 0);
	cairo_set_source_rgb(floatingMiddle, 0, 0, 0);
	cairo_set_source_rgb(floatingBottom, 0, 0, 0);

	/* cairo_move_to(floatingTop, 400, 400);
	cairo_move_to(floatingMiddle, 400, 400);
	cairo_move_to(floatingBottom, 400, 400); */

	// cairo_translate(floatingTop, 400, 400);

	curPos.x = 400;
	curPos.y = 400;
}

Outliner::~Outliner()
{
	cairo_surface_destroy(topSurface);
	cairo_surface_destroy(middleSurface);
	cairo_surface_destroy(bottomSurface);

	cairo_destroy(floatingTop);
	cairo_destroy(floatingMiddle);
	cairo_destroy(floatingBottom);
}

void Outliner::move(double dx, double dy)
{
	curPos.x += dx;
	curPos.y += dy;

	if (!segmentAdded)
	{
		openSegment = NULL;
	}

	segmentAdded = false;

}

const Coordinates &Outliner::getPosition()
{
	return curPos;
}

void Outliner::done()
{

}

void Outliner::maskback(Sketcher *s)
{

}

void Outliner::stamp(Alignment *a)
{
	/* Coordinates coord = curPos;
	stamps.insert(make_pair(a->name(), coord));

	if (NULL != openSegment)
	{
		openSegment->stop = a;
	}
	else
	{
		segments.push_back(openSegment = new Segment(x, y));
		openSegment->start = a;
		segmentAdded = true;
	} */
}


cairo_t *Outliner::top()
{
	return floatingTop;
}

cairo_t *Outliner::middle()
{
	return floatingMiddle;
}

cairo_t *Outliner::bottom()
{
	return floatingBottom;
}

