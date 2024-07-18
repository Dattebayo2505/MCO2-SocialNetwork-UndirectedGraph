// 2024-07-14 Started Initial

#include <stdio.h>
#include "header.h"
#include "graph.h"

int main() {
	FILE *fp;
	int numVertices, startingIndexVertex;

	getNumVertices(&fp, &numVertices);

	SequenceType vertices[numVertices];

	readInput(&fp, vertices, numVertices);

	startingIndexVertex = startIndex(vertices, numVertices);

	createMatrix(vertices, numVertices);
	printVertexDegrees(&fp, vertices, numVertices);

	if (startingIndexVertex != -1) {
		// BFS(startingIndexVertex, adjMatrix);
		// DFS(startingIndexVertex, adjMatrix);
	}
  
  return 0;
}