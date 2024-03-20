// ---------------------------------------------------------
// Name: Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa2
// ---------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Graph.h"
#include "List.h"

/*** Constructors-Destructors ***/

typedef struct GraphObj* Graph;

typedef struct GraphObj {
	int order;
	int size;
	int source;
	List* neighbors;
	char* colors;
	int* parents;
	int* distances;
} GraphObj;

Graph newGraph(int n) {

	if (n <= 0) {
		fprintf(stderr, "Error: Graph must contain at least one vertex.\n");
		exit(EXIT_FAILURE);
	}

	// ALLOCATE memory for Graph object.
	Graph G = malloc(sizeof(GraphObj));

	assert(G != NULL);

	// ASSIGN default values to Graph.
	G->order = n;
	G->size = 0;
	G->source = NIL;

	G->neighbors = (List *) malloc((n + 1) * sizeof(List));
	G->colors = calloc((n + 1), sizeof(char));
	G->parents = calloc((n + 1), sizeof(int));
	G->distances = calloc((n + 1), sizeof(int));

	// INITIALIZE pointers to NULL.
	for (int i = 0; i <= n; i++) {
		G->neighbors[i] = NULL;
	}

	// INITIALIZE the dynamically allocated arrays.
	for (int i = 1; i <= n; i++) {
		G->neighbors[i] = newList();
		G->colors[i] = 'w';
		G->parents[i] = NIL;
		G->distances[i] = INF;
	}

	return G;
}

void freeGraph(Graph *pG) {
	if (pG != NULL && *pG != NULL) {

		// FREE neighbors array.
		for (int i = 1; i <= (*pG)->order; i++) {
			freeList(&((*pG)->neighbors[i]));
		}

		free((*pG)->neighbors);

		// FREE colors array.
		free((*pG)->colors);

		// FREE parents array.
		free((*pG)->parents);

		// FREE distances array.
		free((*pG)->distances);

		// FREE Graph object.
		free(*pG);
		*pG = NULL;
	}
}

/*** Access functions ***/

int getOrder(Graph G) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling getOrder() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	return G->order;
}

int getSize(Graph G) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling getSize() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	return G->size;
}

int getSource(Graph G) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling getSource() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	return G->source;
}

int getParent(Graph G, int u) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling getParent() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	if (u < 1 || u > G->order) {
                fprintf(stderr, "Error: Vertex argument not in the range [1, %d]", G->order);
		exit(EXIT_FAILURE);
        }

	return G->parents[u];
}

int getDist(Graph G, int u) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling getDist() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	if (u < 1 || u > G->order) {
                fprintf(stderr, "Error: Vertex argument not in the range [1, %d]\n", G->order);
		exit(EXIT_FAILURE);
        }

	return G->distances[u];
}

void getPath(List L, Graph G, int u) {
	if (L == NULL) {
                fprintf(stderr, "Error: Calling getPath() on NULL List.\n");
                exit(EXIT_FAILURE);
        }

	if (G == NULL) {
                fprintf(stderr, "Error: Calling getPath() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	if (u < 1 || u > G->order) {
                fprintf(stderr, "Error: Vertex argument not in the range [1, %d]\n", G->order);
		exit(EXIT_FAILURE);
        }

	if (G->source == NIL) {
		fprintf(stderr, "Error: BFS() must be called before getPath() is called.\n");
		exit(EXIT_FAILURE);
	}

	if (G->source == u) { // CHECK if source vertex is same as destination vertex.
		append(L, u);
	} else if (G->parents[u] == NIL) { // CHECK if no path from source to destination exists.
		append(L, NIL);
	} else {
		getPath(L, G, G->parents[u]);
		append(L, u);
	}
}

/*** Helper functions ***/

void sortAppend(List L, int x) {
	if (length(L) <= 0) {
		append(L, x);
		moveFront(L);
	} else {
		moveBack(L);

		while (x < get(L) && index(L) > 0) {
			movePrev(L);
		}
		
		if (x < get(L)) {
                        insertBefore(L, x);
                } else {
                        insertAfter(L, x);
                }
	}
}

/*** Manipulation procedures ***/

void makeNull(Graph G) {
	if (G == NULL) {
		fprintf(stderr, "Error: Calling makeNull() on NULL Graph.\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 1; i <= G->order; i++) {
		freeList(&(G->neighbors[i]));
	}

	for (int i = 1; i <= G->order; i++) {
		G->neighbors[i] = newList();
		G->colors[i] = 'w';
		G->parents[i] = NIL;
		G->distances[i] = INF;
	}

	G->size = 0;
	G->source = NIL;
}

void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling addEdge() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	if (u < 1 || u > G->order) {
		fprintf(stderr, "Error: First vertex argument not in the range [1, %d]\n", G->order);
		exit(EXIT_FAILURE);
	}

	if (v < 1 || v > G->order) {
                fprintf(stderr, "Error: Second vertex argument  not in the range [1, %d]\n", G->order);
		exit(EXIT_FAILURE);
        }

	sortAppend(G->neighbors[u], v);
	sortAppend(G->neighbors[v], u);

	G->size += 1;
}

void addArc(Graph G, int u, int v) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling addArc() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	if (u < 1 || u > G->order) {
                fprintf(stderr, "Error: First vertex argument not in the range [1, %d]\n", G->order);
		exit(EXIT_FAILURE);
        }

        if (v < 1 || v > G->order) {
                fprintf(stderr, "Error: Second vertex argument  not in the range [1, %d]\n", G->order);
		exit(EXIT_FAILURE);
        }

	sortAppend(G->neighbors[u], v);

	G->size += 1;
}

void BFS(Graph G, int s) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling BFS() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	if (s < 1 || s > G->order) {
		fprintf(stderr, "Error: Starting vertex not in range [1, %d].\n", G->order);
		exit(EXIT_FAILURE);
	}

	for (int x = 1; x <= G->order; x++) {
		if (x != s) {
			G->colors[x] = 'w';
			G->distances[x] = INF;
			G->parents[x] = NIL;
		}
	}

	G->colors[s] = 'g';
	G->distances[s] = 0;
	G->parents[s] = NIL;
	G->source = s;

	List L = newList();
	append(L, s);

	while (length(L) > 0) {
		int x = front(L);

		deleteFront(L);
		
		List adj = G->neighbors[x];
		moveFront(adj);

		for (int i = 0; i < length(adj); i++) {
			int y = get(adj);

			if (G->colors[y] == 'w') {
				G->colors[y] = 'g';
				G->distances[y] = G->distances[x] + 1;
				G->parents[y] = x;
				append(L, y);
			}

			moveNext(adj);
		}

		G->colors[x] = 'b';
	}

	freeList(&L);
}

/*** Other operations ***/

void printGraph(FILE* out, Graph G) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling printGraph() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	if (out == NULL) {
		fprintf(stderr, "Error: Could not access file.\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 1; i <= G->order; i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->neighbors[i]);
		fprintf(out, "%s", i==G->order?"":"\n");
	}
}
