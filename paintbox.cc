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

void BoundingBox::stamp(const string &name, Coordinates c)
{
	fallback->stamp(name, c);
}

bool BoundingBox::absorb(Merger *m)
{
	return fallback->absorb(m);
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
 : Merger(true)
{
	segmentAdded = false;
	openSegment = NULL;

	middleSurface = cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, NULL);
	bottomSurface = cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, NULL);

	floatingMiddle = cairo_create(middleSurface);
	floatingBottom = cairo_create(bottomSurface);
}

Outliner::~Outliner()
{
	cairo_surface_destroy(middleSurface);
	cairo_surface_destroy(bottomSurface);
}


bool Outliner::transfer(PaintBox *dst, const string anchor, Coordinates *where)
{
	if (NULL == where)
	{
		cairo_set_source_surface(dst->bottom(), bottomSurface, 0, 0);
		cairo_paint(dst->bottom());

		cairo_set_source_surface(dst->middle(), middleSurface, 0, 0);
		cairo_paint(dst->middle());

		cairo_set_source_surface(dst->top(), topSurface, 0, 0);
		cairo_paint(dst->top());
		return true;
	}
	else
	{
		AlignmentMap::iterator keyPair;

		if (stamps.end() != (keyPair = stamps.find(anchor)))
		{
		Coordinates c = (keyPair->second);

		cairo_set_source_surface(dst->bottom(), bottomSurface, where->x - c.x, where->y - c.y);
		cairo_paint(dst->bottom());

		cairo_set_source_surface(dst->middle(), middleSurface, where->x - c.x, where->y - c.y);
		cairo_paint(dst->middle());

		cairo_set_source_surface(dst->top(), topSurface, where->x - c.x, where->y - c.y);
		cairo_paint(dst->top());

		return true;
		}
	}
	return false;
}

void Outliner::done()
{

}

void Outliner::maskback(Sketcher *s)
{

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

Merger::Merger(bool initOnlyTop)
{
	topSurface =  cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, NULL);
	floatingTop = cairo_create(topSurface);

	if (initOnlyTop)
	{
		floatingMiddle = NULL;
		floatingBottom = NULL;
		return;
	}


	floatingMiddle = cairo_create(topSurface);
	floatingBottom = cairo_create(topSurface);
}

Merger::~Merger()
{
	cairo_surface_destroy(topSurface);

	cairo_destroy(floatingTop);

	if (NULL != floatingMiddle) cairo_destroy(floatingMiddle);
	if (NULL != floatingBottom) cairo_destroy(floatingBottom);
}

void Merger::move(double dx, double dy)
{
	curPos.x += dx;
	curPos.y += dy;
}

bool Merger::transfer(PaintBox *dst, const string anchor, Coordinates *where)
{
	Coordinates c;

	if (NULL == where)
	{
		c.x = 0;
		c.y = 0;
	}
	else
	{
		AlignmentMap::iterator keyPair;

		if (stamps.end() != (keyPair = stamps.find(anchor)))
		{
			c.x = where->x - keyPair->second.x;
			c.y = where->y - keyPair->second.y;
			stamps.erase(keyPair);
		}
		else return false;
	}
	cairo_set_source_surface(dst->top(), topSurface, c.x, c.y);
	cairo_paint(dst->top());

	return true;
}


bool Merger::absorb(Merger *m)
{
	AlignmentMap::iterator stamp = stamps.begin();

	while (stamps.end() != stamp)
	{
		m->transfer(this, stamp->first, &stamp->second);
		stamp++;
	}

	return true;
}

const Coordinates &Merger::getPosition()
{
	return curPos;
}

void Merger::done()
{

}

void Merger::maskback(Sketcher *s)
{

}

void Merger::stamp(Alignment *a)
{
	Coordinates coord = curPos;
	stamps.insert(make_pair(a->name(), coord));
}

void Merger::stamp(const string &name, Coordinates c)
{
	stamps.insert(make_pair(name, c));
}

cairo_t *Merger::top()
{
	return floatingTop;
}

cairo_t *Merger::middle()
{
	return floatingMiddle;
}

cairo_t *Merger::bottom()
{
	return floatingBottom;
}


