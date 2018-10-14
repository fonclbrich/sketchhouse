/**
 * section: Tree
 * synopsis: Navigates a tree to print element names
 * purpose: Parse a file to a tree, use xmlDocGetRootElement() to
 *          get the root element, then walk the document and print
 *          all the element name in document order.
 * usage: tree1 filename_or_URL
 * test: tree1 test2.xml > tree1.tmp && diff tree1.tmp $(srcdir)/tree1.res
 * author: Dodji Seketeli
 * copy: see Copyright for the status of this software.
 */
#include <libxml/parser.h>
#include <iostream>
#include <cairo-ps.h>

#include "housesketcher.h"
#include "output.h"

#ifdef LIBXML_TREE_ENABLED

int main(int argc, char **argv)
{
   /*
    LIBXML_TEST_VERSION

	xmlDoc *doc = xmlReadFile(argv[1], NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", argv[1]);
    }

    xmlNode *root_element = xmlDocGetRootElement(doc);

    //PostScriptWriter leif("plan.ps", {1800, 1800});
    Merger leif;
    cairo_translate(leif.top(), 900, 900);
    cairo_translate(leif.middle(), 900, 900);
    cairo_translate(leif.bottom(), 900, 900);

    HouseSketcher myHouse(&leif);

    myHouse.sketch(root_element->children);

    myHouse.publish();



    xmlFreeDoc(doc);

    xmlCleanupParser(); */


	Outliner house;
	Merger lelle;
	cairo_set_source_rgb(house.middle(), 1, 1, 0);
	cairo_rectangle(house.middle(), 0, 0, 100, 100);
	cairo_fill(house.middle());

	house.transfer(&lelle);

	PostScriptWriter staffan("room2Debug.ps", {1800, 1800});
	cairo_translate(staffan.top(), 900, 900);
	cairo_translate(staffan.middle(), 900, 900);
	cairo_translate(staffan.bottom(), 900, 900);

	lelle.transfer(&staffan);

    return 0;
}
#else

int main(void) {
    fprintf(stderr, "Tree support not compiled in\n");
    exit(1);
}
#endif
