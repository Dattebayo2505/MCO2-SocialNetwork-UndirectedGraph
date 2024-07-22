#include <stdio.h>
#include <string.h>

void DFS(int vertex, SequenceType vertices[], int numVertices, int visited[], char dfsSequence[][MAX_NAMELENGTH])
{
  int i;
  static int tempIndex = 0; // declared as static so the value of tempIndex persists throughout each recursive call

  visited[vertex] = 1; // mark vertex as visited

  printf("%s ", vertices[vertex].vertexID);
  strcpy(dfsSequence[tempIndex], vertices[vertex].vertexID); // store in string array for printing to file
  tempIndex++;

  for (i = 0; i < numVertices; i++)
  {
    if (vertices[vertex].adjMatrixRow[i] == 1 && !visited[i]) {
      DFS(i, vertices, numVertices, visited, dfsSequence);
    }
  }
}

void BFS(int vertex, SequenceType vertices[], int numVertices, int visited[]) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    int currentVertex, i;

    // initialize queue with the start vertex
    visited[vertex] = 1;
    queue[rear++] = vertex;

    while (front < rear) {
        currentVertex = queue[front++];
        printf("%s ", vertices[currentVertex].vertexID);
        //strcpy(bfsSequence[front], vertices[currentVertex].vertexID);

        // Enqueue all adjacent, unvisited vertices (same logic lang sa DFS ish)
        for (i = 0; i < numVertices; i++) {
            if (vertices[currentVertex].adjMatrixRow[i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}