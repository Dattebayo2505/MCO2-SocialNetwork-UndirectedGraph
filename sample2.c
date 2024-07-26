#include "Graphviz-12.0.0-win64/include/graphviz/gvc.h"
#include "Graphviz-12.0.0-win64/include/graphviz/cgraph.h"

int main() {
    GVC_t *gvc;
    Agraph_t *g;
    Agnode_t *n, *m;
    Agedge_t *e;
    FILE *fp;

    // Initialize the graphviz context
    gvc = gvContext();

    // Open a file to read the dot file from
    fp = fopen("input.dot", "r");

    // Read the graph from the file
    g = agread(fp, 0);

    // Close the file
    fclose(fp);

    // Layout the graph using the dot layout engine
    gvLayout(gvc, g, "dot");

    // Render the graph to a file
    gvRenderFilename(gvc, g, "png", "output.png");

    // Free the layout data
    gvFreeLayout(gvc, g);

    // Free the graph
    agclose(g);

    // Free the graphviz context
    gvFreeContext(gvc);

    return 0;
}
