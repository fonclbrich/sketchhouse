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

struct Coordinates
{
	double x;
	double y;
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
public:
	PaintBox();
	virtual ~PaintBox();

	virtual void move(double, double) = 0;
	virtual const Coordinates &getPosition() = 0;

	virtual void done() = 0;
	virtual void maskback(Sketcher *s) = 0;
	virtual void stamp(Alignment *a) = 0;
	virtual void stamp(const string &name, Coordinates c) = 0;
	virtual bool absorb(Merger *m) = 0;

	virtual cairo_t *top() = 0;
	virtual cairo_t *middle() = 0;
	virtual cairo_t *bottom() = 0;
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

	 virtual void maskback(Sketcher *s);
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
	Merger(bool initOnlyTop = false);
	virtual ~Merger();

	virtual void move(double, double);
	virtual const Coordinates &getPosition();
	virtual bool transfer(PaintBox *pb, const string anchor = "", Coordinates *where = NULL);

	virtual void done();
	virtual void maskback(Sketcher *s);
	virtual void stamp(Alignment *a);
	virtual void stamp(const string &name, Coordinates c);
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
	Outliner();
	virtual ~Outliner();

	virtual bool transfer(PaintBox *pb, const string anchor = "", Coordinates *where = NULL);

	virtual void done();
	virtual void maskback(Sketcher *s);

	virtual cairo_t *top();
	virtual cairo_t *middle();
	virtual cairo_t *bottom();
};


#endif /* SKETCHER_H_ */
