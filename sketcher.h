/*
 * sketcher.h
 *
 *  Created on: 2 okt 2018
 *      Author: erik
 */

#ifndef SKETCHER_H_
#define SKETCHER_H_

class Sketcher;
class Alignment;
class PaintBox;
class BoundingBox;
class Merger;
class Path;

class Coordinates
{
public:
	double x;
	double y;

	Coordinates(double nx = 0, double ny = 0);
};

class RGBColor
{
private:
	double r,g,b;

public:
	double blue();
	double green();
	double red();

	RGBColor(unsigned char R, unsigned char G, unsigned char B);
};

#include <list>
#include <map>
#include <iostream>
using namespace std;

typedef map<string, Coordinates> AlignmentMap;
typedef list<AlignmentMap *> MapList;

#include <libxml/parser.h>
#include <cairo.h>
#include "segments.h"

class Sketcher
{
protected:
	PaintBox *paintbox;

public:
	Sketcher(PaintBox *pb);
	virtual ~Sketcher();
	virtual void sketch(xmlNode *node) = 0;
	virtual void publish();
};

class Alignment : public Sketcher
{
private:
	string namestring;

public:
	Alignment(PaintBox *pb);

	virtual void sketch(xmlNode *node);
	const string &name();
};


class PaintBox
{
protected:
	static cairo_rectangle_t ext;

public:
	PaintBox();
	virtual ~PaintBox();

	virtual void move(double, double) = 0;
	virtual const Coordinates &getPosition() = 0;

	virtual void done() = 0;
	virtual void stamp(Alignment *a) = 0;
	virtual void stamp(const string &name, Coordinates c) = 0;
	virtual bool absorb(Merger *m) = 0;

	virtual cairo_t *top() = 0;
	virtual cairo_t *middle() = 0;
	virtual cairo_t *bottom() = 0;
};

class PlainBox : public PaintBox
{

};

class InterceptorPainter : public PaintBox
{
	PaintBox *fallback;

	cairo_surface_t *intTop, *intMid, *intBot;
	cairo_t *it, *im, *ib;

public:
	InterceptorPainter(PaintBox *fb, bool tt = false, bool tm = false, bool tb = false);
	virtual ~InterceptorPainter();

	virtual void move(double, double);
	virtual const Coordinates &getPosition();

	virtual void done();

	virtual void stamp(Alignment *a);
	virtual void stamp(const string &name, Coordinates c);
	virtual bool absorb(Merger *m);

	virtual cairo_t *top();
	virtual cairo_t *middle();
	virtual cairo_t *bottom();
};

class BoundingBox : public PaintBox
{
private:
	cairo_surface_t *boundingBox;
	cairo_t *bc;

	PaintBox *fallback;

public:
	 BoundingBox(PaintBox *fb);
	 virtual ~BoundingBox();

	 virtual void move(double, double);
	 virtual const Coordinates &getPosition();

	 virtual void done();

	 virtual void maskback(PaintBox *src);
	 virtual void stamp(Alignment *a);
	 virtual void stamp(const string &name, Coordinates c);
	 virtual bool absorb(Merger *m);

	 virtual cairo_t *top();
	 virtual cairo_t *middle();
	 virtual cairo_t *bottom();
};

class Merger : public PaintBox
{
protected:
	cairo_surface_t *topSurface;

	cairo_t *floatingTop;
	cairo_t *floatingMiddle;
	cairo_t *floatingBottom;

	Coordinates curPos;

	AlignmentMap stamps;

public:
	Merger(bool initOnlyTop = false, double span = 2000);
	virtual ~Merger();

	virtual void move(double, double);
	virtual const Coordinates &getPosition();
	virtual bool transfer(PaintBox *pb, const string anchor = "", Coordinates *where = NULL);

	virtual void done();
	virtual void stamp(Alignment *a);
	virtual void stamp(const string &name, Coordinates c);
	virtual bool connect(Path *p);
	virtual bool absorb(Merger *m);

	virtual cairo_t *top();
	virtual cairo_t *middle();
	virtual cairo_t *bottom();
};

class Outliner : public Merger
{
private:
	SegmentList segments;
	bool segmentAdded;
	Segment *openSegment;

	cairo_surface_t *middleSurface;
	cairo_surface_t *bottomSurface;

public:
	Outliner(double span = 2000);
	virtual ~Outliner();

	virtual bool transfer(PaintBox *pb, const string anchor = "", Coordinates *where = NULL);

	virtual void done();

	virtual cairo_t *top();
	virtual cairo_t *middle();
	virtual cairo_t *bottom();
};


#endif /* SKETCHER_H_ */
