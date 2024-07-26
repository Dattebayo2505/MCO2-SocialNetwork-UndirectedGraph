// 2024-07-14 Started Initial

#include <stdio.h>

#include "header.h"
#include "graph.h"
#include "traversals.h"

int main() {
  FILE *fp;
  int numVertices, startingIndexVertex;
  int visitedBFS[MAX_VERTICES] = {0};
  int visitedDFS[MAX_VERTICES] = {0};
  stringNames temp = {};

  getNumVertices(&fp, &numVertices);

  SequenceType vertices[numVertices];
  char bfsSequence[numVertices][MAX_NAMELENGTH];
  char dfsSequence[numVertices][MAX_NAMELENGTH];

  readInput(&fp, vertices, numVertices);

  startingIndexVertex = startIndex(vertices, numVertices); 
  strcpy(temp, vertices[startingIndexVertex].vertexID); // For rearrangement later

  sortVertices(vertices, numVertices);

  createAdjMatrix(vertices, numVertices);
  printVertexDegrees(&fp, vertices, numVertices);


  for (int i = 0; i < numVertices; i++) {
    if (strcmp(temp, vertices[i].vertexID) == 0) {
      startingIndexVertex = i;
      break;
    }
  }

  if (startingIndexVertex != -1) {
    printf("\n");
    BFS(startingIndexVertex, vertices, numVertices, visitedBFS, bfsSequence);

    printf("\n");
    DFS(startingIndexVertex, vertices, numVertices, visitedDFS, dfsSequence);

    printTraversalsToFile(&fp, vertices, numVertices, bfsSequence, dfsSequence);
  }

  return 0;
}