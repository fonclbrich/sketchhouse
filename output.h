/*
 * output.h
 *
 *  Created on: 13 okt 2018
 *      Author: erik
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "sketcher.h"
#include <cairo-ps.h>

class PostScriptWriter : public PaintBox
{
private:
	PaintBox *fallback;

	cairo_surface_t *surf;

	cairo_t *floatingTop;
	cairo_t *floatingMiddle;
	cairo_t *floatingBottom;

public:
	PostScriptWriter(const string filename, const Coordinates size, PaintBox *fb = NULL);
	virtual ~PostScriptWriter();

	virtual void move(double dx, double y);
	virtual const Coordinates &getPosition();

	virtual void done();
	virtual void maskback(Sketcher *s);
	virtual void stamp(Alignment *a);
	virtual void stamp(const string &name, Coordinates c);
	virtual bool absorb(Merger *m);

	virtual cairo_t *top();
	virtual cairo_t *middle();
	virtual cairo_t *bottom();


};


#endif /* OUTPUT_H_ */
