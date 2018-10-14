/*
 * pathsketcher.h
 *
 *  Created on: 13 okt 2018
 *      Author: erik
 */

#ifndef PATHSKETCHER_H_
#define PATHSKETCHER_H_

#include "geometryobject.h"

class Path : public GeometryObject
{
private:
	string orig;
	string dest;

	void translateOrigin(xmlNode *node);
	void translateDestination(xmlNode *node);

public:
	Path();

	const string &origin();
	const string &destination();

	const Coordinates offset();
};


#endif /* PATHSKETCHER_H_ */
