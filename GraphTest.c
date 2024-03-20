// ---------------------------------------------------------
// Name: Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa2
// ---------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {

	FILE* out = stdout;

	fprintf(out, "\n");

	fprintf(out, "Creating Graphs G1, G2\n\n");

	Graph G1 = newGraph(1);
	Graph G2 = newGraph(5);

	fprintf(out, "Freeing Graphs G1, G2\n\n");

	fprintf(out, "getOrder(G1): %d\ngetOrder(G2): %d\n\n", getOrder(G1), getOrder(G2));

	fprintf(out, "getSize(G1): %d\ngetSize(G2): %d\n\n", getSize(G1), getSize(G2));

	fprintf(out, "getSource(G1): %d\ngetSource(G2): %d\n\n", getSource(G1), getSource(G2));

	fprintf(out, "getParent(G1): %d\ngetParent(G2): %d\n\n", getParent(G1, 1), getParent(G2, 5));

	fprintf(out, "getDist(G1): %d\ngetDist(G2): %d\n\n", getDist(G1, 1), getDist(G2, 4));

	fprintf(out, "BFS(G1)\nBFS(G2)\n\n");

	BFS(G1, 1);
	BFS(G2, 4);
	
	fprintf(out, "getPath(G1)\ngetPath(G2)\n\n");

	List L1 = newList();
	List L2 = newList();

	getPath(L1, G1, 1);
	getPath(L2, G2, 5);

	freeGraph(&G1);
	freeGraph(&G2);

	freeList(&L1);
	freeList(&L2);

	return EXIT_SUCCESS;
}
