/*
 * delegatesketcher.h
 *
 *  Created on: 30 sep 2018
 *      Author: erik
 */

#ifndef DELEGATESKETCHER_H_
#define DELEGATESKETCHER_H_


#include "sketcher.h"
#include <map>

using namespace std;

class DelegateSketcher;

typedef void (DelegateSketcher::*Delegate)(xmlNode *node);

class DelegateSketcher : public Sketcher
{
private:
	map<string, Delegate> delegates;
	virtual void prologue();
	virtual void epilogue();

protected:
	void addDelegate(string keyword, Delegate delegate);
	int callCount;

public:
	DelegateSketcher(PaintBox *);
	virtual void sketch(xmlNode *node);
};

#endif /* DELEGATESKETCHER_H_ */
