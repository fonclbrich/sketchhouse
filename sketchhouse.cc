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
#include <string>
#include <iostream>

#include "housesketcher.h"
#include "output.h"

#ifdef LIBXML_TREE_ENABLED

int main(int argc, char **argv)
{
    LIBXML_TEST_VERSION

	xmlDoc *doc = xmlReadFile(argv[1], NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", argv[1]);
    }

    xmlNode *root_element = xmlDocGetRootElement(doc);

    PostScriptWriter leif("plan.ps", {6000, 6000});
    //Merger leif;

    HouseSketcher myHouse(&leif);

    myHouse.sketch(root_element->children);

    myHouse.publish();

   /*  Outliner leif;

    cairo_set_source_rgb(leif.middle(), 0, 0,1);
    cairo_rectangle(leif.middle(), 0, 0, 100, 100);
    cairo_fill(leif.middle()); */


    xmlFreeDoc(doc);

    xmlCleanupParser();

    return 0;
}
#else

int main(void) {
    fprintf(stderr, "Tree support not compiled in\n");
    exit(1);
}
#endif
