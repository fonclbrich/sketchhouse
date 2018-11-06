/*
 * output.cc
 *
 *  Created on: 13 okt 2018
 *      Author: erik
 */

#include "output.h"

PostScriptWriter::PostScriptWriter(const string filename, const Coordinates size, PaintBox *fb)
{
	fallback = fb;

	surf = cairo_ps_surface_create(filename.c_str(), size.x, size.y);
	floatingTop = cairo_create(surf);
	floatingMiddle = cairo_create(surf);
	floatingBottom = cairo_create(surf);
}

PostScriptWriter::~PostScriptWriter()
{
	cairo_surface_destroy(surf);

	cairo_destroy(floatingTop);
	cairo_destroy(floatingMiddle);
	cairo_destroy(floatingBottom);
}


void PostScriptWriter::move(double dx, double dy)
{
	if (NULL != fallback) fallback->move(dx, dy);
}


const Coordinates &PostScriptWriter::getPosition()
{
	if (NULL != fallback)
		return fallback->getPosition();

	Coordinates origin;
	return origin;
}

void PostScriptWriter::done()
{
	if (NULL != fallback) fallback->done();
}

void PostScriptWriter::stamp(Alignment *a)
{
	if (NULL != fallback) fallback->stamp(a);
}

void PostScriptWriter::stamp(const string &name, Coordinates c)
{
	if (NULL != fallback) fallback->stamp(name, c);
}

bool PostScriptWriter::absorb(Merger *m)
{
	if (NULL != fallback) return fallback->absorb(m); else return false;
}

cairo_t *PostScriptWriter::top()
{
	return floatingTop;
}

cairo_t *PostScriptWriter::middle()
{
	return floatingMiddle;
}

cairo_t *PostScriptWriter::bottom()
{
	return floatingBottom;
}

