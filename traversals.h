#include <stdio.h>
#include <string.h>

void DFS(int vertex, SequenceType vertices[], int numVertices, int visited[])
{
  int i;

  visited[vertex] = 1; // mark vertex as visited

  printf("%s ", vertices[vertex].vertexID);
  for (i = 0; i < numVertices; i++)
  {
    if (vertices[vertex].adjMatrixRow[i] == 1 && !visited[i])
      DFS(i, vertices, numVertices, visited);
  }
}