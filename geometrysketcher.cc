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
		cairo_move_to(paintbox->top(), wallStart.x, wallStart.y);

		while (!wallPieces.empty())
		{
			WallSketcher *piece = *wallPieces.begin();
			piece->publish();
			delete piece;
			wallPieces.pop_front();
		}

		cairo_stroke(paintbox->top());

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
}

void GeometrySketcher::sketch(xmlNode *node)
{
	DelegateSketcher::sketch(node);

	didWall = false;
	prologue();
	bb->done();
}
