/*
 * housesketcher.h
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */

#ifndef HOUSESKETCHER_H_
#define HOUSESKETCHER_H_


#include "pathsketcher.h"

typedef std::list<Merger *> MergerList;
typedef std::list<Path *> PathList;

class HouseSketcher : public DelegateSketcher
{
private:
	MergerList roomSketches;
	PathList paths;

	void doRoom(xmlNode *);
	void doPath(xmlNode *);

public:
	HouseSketcher(PaintBox *pb);
	~HouseSketcher();

	virtual void sketch(xmlNode *node);
	virtual void publish();
};


#endif /* HOUSESKETCHER_H_ */
