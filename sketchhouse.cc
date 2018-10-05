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

#ifdef LIBXML_TREE_ENABLED

int main(int argc, char **argv)
{
    if (argc != 2)
        return(1);

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
	xmlDoc *doc = xmlReadFile(argv[1], NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", argv[1]);
    }

    /*Get the root element node */
    xmlNode *root_element = xmlDocGetRootElement(doc);

    HouseSketcher myHouse(NULL);

    myHouse.sketch(root_element->children);

	cairo_surface_t *plan = cairo_ps_surface_create("plan.ps", 400, 400);
	cairo_t *bc = cairo_create(plan);

	cairo_set_source_rgb(bc, 0, 0, 0);
	cairo_set_line_width(bc, 1);

	cairo_move_to(bc, 200, 200);

    myHouse.publish(bc);

    cairo_surface_show_page(plan);

	cairo_destroy(bc);
	cairo_surface_finish(plan);
	cairo_surface_destroy(plan);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    return 0;
}
#else

int main(void) {
    fprintf(stderr, "Tree support not compiled in\n");
    exit(1);
}
#endif
