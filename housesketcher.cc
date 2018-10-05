/*
 * housesketcher.cc
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */


#include "housesketcher.h"
#include "roomsketcher.h"
#include <iostream>

using namespace std;

HouseSketcher::HouseSketcher(PaintBox *pb)
	: DelegateSketcher(pb)
{
	addDelegate("room", (Delegate) &HouseSketcher::doRoom);
	addDelegate("connect", (Delegate) &HouseSketcher::doConnect);
}

HouseSketcher::~HouseSketcher()
{

}

void HouseSketcher::sketch(xmlNode *node)
{
	DelegateSketcher::sketch(node);

	// Now clear up loose walls

}

void HouseSketcher::doRoom(xmlNode *node)
{
	/* SegmentList *wallSegments = new SegmentList;
	wallCollection.push_back(wallSegments);

	AlignmentMap *wallAlignments = new AlignmentMap;
	stampCollection.push_back(wallAlignments); */

	Outliner wallOutlines;
	RoomSketcher room(&wallOutlines);


	room.sketch(node);
	cairo_show_page(wallOutlines.top());
}

void HouseSketcher::doConnect(xmlNode *node)
{
	string input = (char *) xmlNodeGetContent(node);

	size_t comma = input.find_first_of(",");

	string source = input.substr(1, comma - 1);
	string target = input.substr(comma + 1);
	cout << source << endl;
	cout << target << endl;


}

void HouseSketcher::publish(cairo_t *cs)
{
/*	 SegmentCollection::iterator segmentList = wallCollection.begin();

	 while(wallCollection.end() != segmentList)
	 {
		 SegmentList::iterator segment = (*segmentList)->begin();

		 while ((*segmentList)->end() != segment)
		 {
			 Coordinates noChange = {0,0};
			 PieceList::iterator firstPiece = (*segment)->pieces.begin();

			 cairo_move_to(cs, (*segment)->x,(*segment)->y);
			 (*firstPiece)->traceback(cs, noChange, firstPiece, (*segment)->pieces.end());

			 cairo_close_path(cs);
			 cairo_stroke_preserve(cs);
			 cairo_fill(cs);

			 segment++;
		 }
		 segmentList++;
	 }
	 */
}
