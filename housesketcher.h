/*
 * housesketcher.h
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */

#ifndef HOUSESKETCHER_H_
#define HOUSESKETCHER_H_


#include "delegatesketcher.h"
#include "segments.h"

class HouseSketcher : public DelegateSketcher
{
private:
	SegmentCollection wallCollection;
	MapList stampCollection;

	void doRoom(xmlNode *);
	void doConnect(xmlNode *);

public:
	HouseSketcher(PaintBox *pb);
	~HouseSketcher();

	virtual void sketch(xmlNode *node);
	virtual void publish(cairo_t *cs);
};


#endif /* HOUSESKETCHER_H_ */
