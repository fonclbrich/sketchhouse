/*
 * alignment.cc
 *
 *  Created on: 2 okt 2018
 *      Author: erik
 */




#include "sketcher.h"

Alignment::Alignment(PaintBox *pb)
 : Sketcher(pb)
{

}

void Alignment::sketch(xmlNode *node)
{
	namestring = (const char *)xmlNodeGetContent(node);
}

const std::string &Alignment::name()
{
	return namestring;
}

