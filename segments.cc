/*
 * segments.cc
 *
 *  Created on: 2 okt 2018
 *      Author: erik
 */


#include "segments.h"
#include <cstdlib>

Segment::Segment(double nx, double ny)
{
	x = nx;
	y = ny;
	start = stop = NULL;
}
