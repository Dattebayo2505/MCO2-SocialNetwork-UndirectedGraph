#include <stdio.h>
#include <string.h>

#include "header.h"
#include "graph.c"
#include "traversals.c"

int main() {
  FILE *fp;
  int numVertices, startingIndexVertex, i;
  int visitedBFS[MAX_VERTICES] = {0};
  int visitedDFS[MAX_VERTICES] = {0};
  stringNames temp = {};

  getNumVertices(&fp, &numVertices);

  SequenceType vertices[numVertices];
  char bfsSequence[numVertices][MAX_NAMELENGTH];
  char dfsSequence[numVertices][MAX_NAMELENGTH];

  readInput(&fp, vertices, numVertices);

  startingIndexVertex = startIndex(vertices, numVertices);
  strcpy(temp, vertices[startingIndexVertex].vertexID); // For rearrangement later since made alphabetical

  sortVertices(vertices, numVertices);

  createAdjMatrix(vertices, numVertices);
  printVertexDegrees(&fp, vertices, numVertices);

  reSortStartVertexIndex(vertices, temp, numVertices, &startingIndexVertex); // Rearrange vertices to original order

  if (startingIndexVertex != -1) {
    BFS(startingIndexVertex, vertices, numVertices, visitedBFS, bfsSequence);
    DFS(startingIndexVertex, vertices, numVertices, visitedDFS, dfsSequence);

    printTraversalsToFile(&fp, vertices, numVertices, bfsSequence, dfsSequence);
  }

  return 0;
}