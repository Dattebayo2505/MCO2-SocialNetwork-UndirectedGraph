// 2024-07-14 Started Initial

#include <stdio.h>
#include "header.h"
#include "graph.h"

int main() {
	FILE *fp;
	int numVertices, startingIndex;

	getNumVertices(&fp, &numVertices);

	SequenceType vertices[numVertices];

	readInput(&fp, vertices, numVertices);

	startingIndex = startIndex(vertices, numVertices);

	createMatrix(vertices, numVertices); // DEBUGGING
	printVertexDegrees(&fp, vertices, numVertices);


	if (startingIndex != -1) {
		// BFS(startingIndex);
		// DFS(startingIndex);
	}
  
  return 0;
}