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

void printPath(FILE* out, Graph G, int s, int d, int counter, List L) {
	if (s == d) { // PRINTS the last reachable vertex.
		if (counter >= 1) {
			fprintf(out, "%d\n", counter);
		} else {
			fprintf(out, "The distance from %d to %d is 0\n", s, d);
			fprintf(out, "A shortest %d-%d path is: %d\n", s, d, d);
		}
	} else if (getParent(G, d) == NIL) { // PRINTS when destination vertex is not reachable from source vertex.
		fprintf(out, "The distance from %d to %d is infinity\n", s, d);
                fprintf(out, "No %d-%d path exists\n", s, d);
	} else { // RECURSIVELY calls printPath() and prints all reachable vertices.
		counter += 1;

		if (counter == 1) {
			fprintf(out, "The distance from %d to %d is ", s, d);
		}

		printPath(out, G, s, getParent(G, d), counter, L);

		if (counter == 1) {
			fprintf(out, "A shortest %d-%d path is: ", s, d);

			getPath(L, G, d);

			moveFront(L);

			while (length(L) > 0) {
				fprintf(out, "%d%s", front(L), length(L)==1?"": " ");
				moveNext(L);
				deleteFront(L);	
			}

			fprintf(out, "\n");
		}
	}
}

int main(int argc, char * argv[]) {

	FILE *in, *out;

	// CHECK that there are exactly two command line arguments.
	
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// OPEN files for reading and writing.

	in = fopen(argv[1], "r");

	if (in == NULL) {
		fprintf(stderr, "Unable to open file %s for reading.\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	out = fopen(argv[2], "w");

        if (out == NULL) {
                fprintf(stderr, "Unable to open file %s for writing.\n", argv[2]);
                exit(EXIT_FAILURE);
        }

	// SCAN first line, representing number of vertices.

	int numOfVertices;

	fscanf(in, "%d", &numOfVertices);

	// CREATE a new Graph object.	

	Graph G = newGraph(numOfVertices);

	// READ each vertex pair and store them in the List array.

	int v1, v2;

	fscanf(in, "%d %d", &v1, &v2);

	while (v1 != 0 || v2 != 0) {

		// ADD edge pairs of vertices.
		addEdge(G, v1, v2);

		// READ neext pair of vertices.
		fscanf(in, "%d %d", &v1, &v2);
	}

	// PRINT the adjacency list representation.
	
	printGraph(out, G);

	// READ vertices and find shortest path between them.
	
	int source, destination;

	fscanf(in, "%d %d", &source, &destination);

	while (source != 0 || destination != 0) {
		fprintf(out, "\n");

		// PERFORM Breadth First Search.
		BFS(G, source);

		// PRINT out shortest path from source to destination.
		List shortest = newList();
		int counter = 0;

		printPath(out, G, source, destination, counter, shortest);

		// READ next pair of vertices.
		fscanf(in, "%d %d", &source, &destination);

		// DEALLOCATE List object.
		freeList(&shortest);
	}

	// CLOSE files and DEALLOCATE memory.
	
	fclose(in);
	fclose(out);

	freeGraph(&G);

	return EXIT_SUCCESS;
}
