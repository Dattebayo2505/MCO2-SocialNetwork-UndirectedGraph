// 2024-07-14 Started Initial

#include <stdio.h>

#include "header.h"
#include "graph.h"
#include "traversals.h"

int main() {
  FILE *fp;
  int numVertices, startingIndexVertex;
  int visitedBFS[MAX_VERTICES] = {0}; // idk if need iseparate yung visited array -meg
  int visitedDFS[MAX_VERTICES] = {0};

  getNumVertices(&fp, &numVertices);

  SequenceType vertices[numVertices];
  char bfsSequence[numVertices][MAX_NAMELENGTH];
  char dfsSequence[numVertices][MAX_NAMELENGTH]; // stores the names of vertices visited in the order of DFS traversal

  readInput(&fp, vertices, numVertices);

  startingIndexVertex = startIndex(vertices, numVertices);

  createMatrix(vertices, numVertices);
  printVertexDegrees(&fp, vertices, numVertices);

  if (startingIndexVertex != -1) {
    printf("\n");
    BFS(startingIndexVertex, vertices, numVertices, visitedBFS);

    printf("\n");
    DFS(startingIndexVertex, vertices, numVertices, visitedDFS, dfsSequence);
  }
  
 // printTraversalsToFile(&fp, vertices, numVertices, dfsSequence, bfsSequence);

  return 0;
}