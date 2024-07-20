// 2024-07-14 Started Initial

#include <stdio.h>

#include "header.h"
#include "graph.h"
#include "traversals.h"

int main() {
  FILE *fp;
  int numVertices, startingIndexVertex;
  int visited[MAX_VERTICES] = {0};

  getNumVertices(&fp, &numVertices);

  SequenceType vertices[numVertices];
  SequenceType vertex;

  readInput(&fp, vertices, numVertices);

  startingIndexVertex = startIndex(vertices, numVertices);

  int adjMatrix[numVertices][numVertices];
  //getAdjMatrixFromMatrixRow(vertex, adjMatrix, numVertices);
  createMatrix(vertices, numVertices); // vertices[] is already populated atp
  printVertexDegrees(&fp, vertices, numVertices);

  if (startingIndexVertex != -1) {
    // BFS(startingIndexVertex, adjMatrix);
    
    printf("\n");
    DFS(startingIndexVertex, vertices, numVertices, visited);
  }

  return 0;
}