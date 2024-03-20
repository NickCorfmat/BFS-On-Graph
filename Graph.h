// ---------------------------------------------------------
// Name: Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa2
// ---------------------------------------------------------

#ifndef GRAPH_H_
#define GRAPH_H_

#pragma once

#define INF -1 // Negative int to represent infinity
#define NIL 0 // Non-positive int to represent an undefined vertex label

#include <stdlib.h>
#include <stdio.h>

#include "List.h"

/*** Constructors-Destructors ***/

typedef struct GraphObj* Graph;

Graph newGraph(int n);

void freeGraph(Graph *pG);

/*** Access functions ***/

int getOrder(Graph G);

int getSize(Graph G);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/

void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

/*** Other operations ***/

void printGraph(FILE* out, Graph G);

#endif
