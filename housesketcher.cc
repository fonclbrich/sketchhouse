/*
 * housesketcher.cc
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */


#include "housesketcher.h"
#include "roomsketcher.h"
#include <iostream>
#include "output.h"
#include <cairo-ps.h>

using namespace std;

HouseSketcher::HouseSketcher(PaintBox *pb)
	: DelegateSketcher(pb)
{
	addDelegate("room", (Delegate) &HouseSketcher::doRoom);
	addDelegate("path", (Delegate) &HouseSketcher::doPath);
}

HouseSketcher::~HouseSketcher()
{
	while (!roomSketches.empty())
	{
		delete *roomSketches.begin();
		roomSketches.pop_front();
	}

	while (!paths.empty())
	{
		delete *paths.begin();
		paths.pop_front();
	}
}

void HouseSketcher::sketch(xmlNode *node)
{
	DelegateSketcher::sketch(node);

	// Now clear up loose walls

}

void HouseSketcher::doRoom(xmlNode *node)
{
	Outliner *wallOutlines = new Outliner;
	RoomSketcher room(wallOutlines);

	room.sketch(node);

	roomSketches.push_back(wallOutlines);
}

void HouseSketcher::doPath(xmlNode *node)
{
	Path *path = new Path();
	path->sketch(node);

	paths.push_back(path);
}

void HouseSketcher::publish()
{

	Outliner house;
	cairo_identity_matrix(house.top());
	cairo_identity_matrix(house.middle());
	cairo_identity_matrix(house.bottom());

	Coordinates origin;

	if (paths.empty())
	{
		// Handle empty
	}

	PathList::iterator path = paths.begin();

	house.stamp((**path).origin(), origin);
	house.stamp((**path).destination(), (**path).offset());

	paths.pop_front();

	bool didSomething = true;

	while (!roomSketches.empty() && didSomething)
	{
		didSomething = false;
		MergerList::iterator room = roomSketches.begin();

		while (roomSketches.end() != room)
		{
			if (house.absorb(*room))
			{
				delete *room;
				roomSketches.erase(room);
				didSomething = true;
				break;
			}
			room++;
		}

		path = paths.begin();

		while (paths.end() != path)
		{
			if (house.connect(*path))
			{
				delete *path;
				paths.erase(path);
				didSomething = true;
				break;
			}
			path++;
		}
	}

	house.transfer(paintbox);
}

