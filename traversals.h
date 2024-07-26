#include <stdio.h>
#include <string.h>

/**
 * Performs a Depth-First Search (DFS) traversal starting from a given vertex.
 *
 * @param vertex The starting vertex for the DFS traversal.
 * @param vertices An array of SequenceType representing the vertices in the graph.
 * @param numVertices The total number of vertices in the graph.
 * @param visited An array of integers representing the visited status of each vertex.
 * @param dfsSequence A 2D character array to store the DFS traversal sequence.
 */
void DFS(int vertex, SequenceType vertices[], int numVertices, int visited[], char dfsSequence[][MAX_NAMELENGTH]) {
  int i;
  static int tempIndex = 0; // declared as static so the value of tempIndex persists throughout each recursive call

  visited[vertex] = 1; // mark vertex as visited

  printf("%s ", vertices[vertex].vertexID);
  strcpy(dfsSequence[tempIndex], vertices[vertex].vertexID); // store in string array for printing to file
  tempIndex++;

  for (i=0; i<numVertices; i++) {
    if (vertices[vertex].adjMatrixRow[i] == 1 && !visited[i]) {
      DFS(i, vertices, numVertices, visited, dfsSequence);
    }
  }
}

/**
 * Performs a Breadth-First Search (BFS) traversal starting from a given vertex.
 *
 * @param vertex The starting vertex for the BFS traversal.
 * @param vertices An array of SequenceType representing the vertices in the graph.
 * @param numVertices The total number of vertices in the graph.
 * @param visited An array of integers representing the visited status of each vertex.
 * @param bfsSequence A 2D character array to store the BFS traversal sequence.
 */
void BFS(int vertex, SequenceType vertices[], int numVertices, int visited[], char bfsSequence[][MAX_NAMELENGTH]) {
  int queue[MAX_VERTICES];
  int front = 0, rear = 0, bfsIndex = 0; // Added bfsIndex to track position in bfsSequence
  int currentVertex, i;

  // initialize queue with the start vertex
  visited[vertex] = 1;
  queue[rear++] = vertex;

  while (front < rear) {
    currentVertex = queue[front++];
    printf("%s ", vertices[currentVertex].vertexID);
    if (bfsIndex < MAX_VERTICES) { // Ensure we don't exceed bounds of bfsSequence
      strcpy(bfsSequence[bfsIndex++], vertices[currentVertex].vertexID); // Use bfsIndex instead of front
    }

    // Enqueue all adjacent, unvisited vertices
    for (i=0; i<numVertices; i++) {
      if (vertices[currentVertex].adjMatrixRow[i] == 1 && !visited[i]) {
        visited[i] = 1;
        queue[rear++] = i;
      }
    }
  }
}

/**
 * Writes the BFS and DFS traversal sequences to a file.
 *
 * This function takes in the file pointer, an array of vertices, the number of vertices,
 * the BFS sequence, and the DFS sequence. It opens the file "TRAVERSALS.txt" in append mode,
 * writes the BFS sequence followed by a newline character, writes the DFS sequence followed
 * by a newline character, and then closes the file.
 *
 * @param fp The file pointer to write the traversal sequences to.
 * @param vertices The array of vertices.
 * @param numVertices The number of vertices.
 * @param bfsSequence The BFS traversal sequence.
 * @param dfsSequence The DFS traversal sequence.
 */
void printTraversalsToFile(FILE **fp, SequenceType vertices[], int numVertices, char bfsSequence[][MAX_NAMELENGTH], char dfsSequence[][MAX_NAMELENGTH]) {
  int i;
  *fp = fopen("TRAVERSALS.txt", "a");

  // BFS
  fprintf(*fp, "\n");
  for (i=0; i<numVertices; i++) {
    fprintf(*fp, "%s ", bfsSequence[i]);
  }

  fprintf(*fp, "\n");

  // DFS
  fprintf(*fp, "\n");
  for (i=0; i<numVertices; i++) {
    fprintf(*fp, "%s ", dfsSequence[i]);
  }
  fclose(*fp);
}