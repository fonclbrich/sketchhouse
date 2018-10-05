/*
 * segments.h
 *
 *  Created on: 2 okt 2018
 *      Author: erik
 */

#ifndef SEGMENTS_H_
#define SEGMENTS_H_

class Segment;
class WallSketcher;
class Alignment;

#include <list>

typedef std::list<WallSketcher *> PieceList;
typedef std::list<Segment *> SegmentList;
typedef std::list<SegmentList *> SegmentCollection;

class Segment
{
public:
	double x;
	double y;

	Alignment *start;
	Alignment *stop;

	PieceList pieces;

	Segment(double nx, double ny);
};



#endif /* SEGMENTS_H_ */
