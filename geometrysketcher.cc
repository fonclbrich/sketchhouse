/*
 * geometrysketcher.cc
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */

#include "geometrysketcher.h"
#include "wallsketcher.h"
#include "windowsketcher.h"
#include <iostream>

void GeometrySketcher::prologue()
{
	if (!didWall && !wallPieces.empty() )
	{
		cairo_set_source_rgb(paintbox->top(), 0,0,0);
		cairo_set_source_rgb(paintbox->bottom(), 0,0,0);
		cairo_set_source_rgb(paintbox->middle(), 0,0.8,0);
		cairo_move_to(paintbox->top(), wallStart.x, wallStart.y);
		cairo_move_to(paintbox->middle(), wallStart.x, wallStart.y);

		Coordinates noChange = {0,0};
		(**wallPieces.begin()).traceback(noChange, wallPieces.begin(), wallPieces.end());
		(**wallPieces.begin()).tracebackP(noChange, wallPieces.begin(), wallPieces.end());
		(**wallPieces.begin()).publish();


		while (!wallPieces.empty())
		{
			delete *wallPieces.begin();
			wallPieces.pop_front();
		}

		cairo_stroke(paintbox->top());
		cairo_stroke(paintbox->bottom());
		cairo_fill(paintbox->middle());
	}
	didWall = false;
}

GeometrySketcher::GeometrySketcher(PaintBox *pb)
	: DelegateSketcher(pb)
{
	bb = new BoundingBox(pb);

	addDelegate("wall", (Delegate) &GeometrySketcher::doWall);
	addDelegate("window", (Delegate) &GeometrySketcher::doWindow);
	addDelegate("align", (Delegate) &GeometrySketcher::doAlign);

	didWall = false;

	wallStart.x = 0;
	wallStart.y = 0;
}

GeometrySketcher::~GeometrySketcher()
{
	delete bb;
}

void GeometrySketcher::doWall(xmlNode *node)
{
	if (wallPieces.empty())
	{
		wallStart = paintbox->getPosition();
	}

	WallSketcher *wall = new WallSketcher(bb);
	wallPieces.push_back(wall);
	wall->sketch(node);
	didWall = true;
}

void GeometrySketcher::doWindow(xmlNode *node)
{
	WindowSketcher window(bb);
	window.sketch(node);
}

void GeometrySketcher::doAlign(xmlNode *node)
{
	Alignment *alignment = new Alignment(paintbox);
	alignment->sketch(node);
	paintbox->stamp(alignment);
	didWall = true;
}

void GeometrySketcher::sketch(xmlNode *node)
{
	DelegateSketcher::sketch(node);

	didWall = false;
	prologue();
	bb->done();
}
