/*
 * delegatesketcher.cc
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */


#include "delegatesketcher.h"
#include <iostream>

void DelegateSketcher::prologue()
{

}


void DelegateSketcher::epilogue()
{

}

DelegateSketcher::DelegateSketcher(PaintBox *pb)
  : Sketcher(pb)
{
	callCount = 0;
}

void DelegateSketcher::addDelegate(string keyword, Delegate delegate)
{
	delegates.insert(make_pair(keyword, delegate));
}

void DelegateSketcher::sketch(xmlNode *roomNode)
{
	xmlNode *currentNode = roomNode;

	while(NULL != currentNode)
	{
		map<string, Delegate>::iterator keyPair;

		if (delegates.end() != (keyPair = delegates.find((const char *) currentNode->name)))
		{
			prologue();
			(this->*keyPair->second)(currentNode->children);
			epilogue();
		}

		currentNode = currentNode->next;
	}

}

