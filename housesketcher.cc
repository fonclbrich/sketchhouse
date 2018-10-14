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

	Coordinates origin = {0,0};

	PathList::iterator path = paths.begin();

//	house.stamp((**path).origin(), origin);
//	house.stamp((**path).destination(), (**path).offset());

	MergerList::iterator room = roomSketches.begin();

	while (roomSketches.end() != room)
	{
		PostScriptWriter staffan("roomDebug.ps", {1800, 1800});
		cairo_translate(staffan.top(), 900, 900);
		cairo_translate(staffan.middle(), 900, 900);
		cairo_translate(staffan.bottom(), 900, 900);

		(**room).transfer(&staffan);

	//	(**room).transfer(&house);
//		house.absorb(*room);
		room++;
	}


}

