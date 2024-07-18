#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void resetArray(char input[], int size) { 
  memset(input, 0, size); 
}

void readInput(FILE **fp, SequenceType vertices[], int numVertices) {
  stringNames temp = {};
  int fScanfResult = 0,
      vertexIDCtr = 0, 
      neighborCtr = 0;
      
  while(fScanfResult != EOF) {
    fScanfResult = fscanf(*fp, "%s", temp);

    if (strcmp(temp, "-1") != 0)
      strcpy(vertices[vertexIDCtr].vertexID, temp);

    while (strcmp(temp, "-1") != 0 && fScanfResult != EOF) {
      fScanfResult = fscanf(*fp, "%s", temp);

      if (strcmp(temp, "-1") != 0 && fScanfResult != EOF) {
        strncpy(vertices[vertexIDCtr].neighbors[neighborCtr], temp, MAX_NAMELENGTH - 1);
        neighborCtr++;
      }
    }
    if (fScanfResult != EOF) {
      vertices[vertexIDCtr].neighborTotal = neighborCtr;
      resetArray(temp, sizeof(stringNames));
      neighborCtr = 0;
      ++vertexIDCtr;
    }
  }
  fclose(*fp);
}

int isValidName(SequenceType vertices[], int numVertices, char inputName[]) {
  int i;

  for (i=0; i<numVertices; i++) {
    if (strcmp(vertices[i].vertexID, inputName) == 0)
      return i;
  }
  return 0;
}

int startIndex(SequenceType vertices[], int numVertices) {
    stringNames startVertex;
    int indexVertex;

    printf("Input start vertex for the traversal: ");
    scanf("%s", startVertex);

    indexVertex = isValidName(vertices, numVertices, startVertex);
    if (!indexVertex) {
      printf("Vertex %s not found.\n", startVertex);
      return -1;
    }

    return indexVertex;
}

void getNumVertices(FILE **fp, int *numVertices) {
  char filename[MAX_FILENAME_LENGTH];

  printf("Input filename: ");
  // scanf("%s", filename); // Un-comment out
  printf("GRAPH.txt\n"); strcpy(filename, "GRAPH.txt"); // DEBUGGING
  *fp = fopen(filename, "r");

  if (*fp == NULL) {
    printf("%s not found.\n", filename);
    return;
  }
  else
    fscanf(*fp, "%d", numVertices);
}

// DEBUGGING ONLY
void printGraph(SequenceType vertices[], int numVertices) {
  for (int i = 0; i < numVertices; i++) {
    for (int j = 0; j < numVertices; j++) {
      printf("%d ", vertices[i].adjMatrixRow[j]);
    }
    printf("\n");
  }
  printf("\n");
}

void createMatrix(SequenceType vertices[], int numVertices) {
  
  int neighborCtr = 0, i, j;
  
  for (i = 0; i < numVertices; i++) {
    for (j = 0; j < numVertices; j++)
      vertices[i].adjMatrixRow[j] = 0;
  }

  for (i=0; i<numVertices; i++) {
    vertices[i].degree = 0;

    for (j=0; j<numVertices; j++) {
      while (strcmp(vertices[i].neighbors[neighborCtr], vertices[j].vertexID) == 0
             && vertices[i].neighborTotal > neighborCtr) { // only works when names are alphabetical (WILL FIX SOON)
        // adjMatrix[i][j] = 1; // debugging
        vertices[i].adjMatrixRow[j] = 1;
        ++vertices[i].degree;
        ++neighborCtr;
      }
    }
    neighborCtr = 0; 
  }

  printGraph(vertices, numVertices); // DEBUGGING
}

int longestString(SequenceType vertices[], int numVertices) {
  int currentLength, maxLength = 0, i;

  for (i=0; i<numVertices; i++) {
    currentLength = strlen(vertices[i].vertexID);
    if (currentLength > maxLength) {
    maxLength = currentLength;
    }
  }
  return maxLength;
}

void printVertexDegrees(FILE **fp, SequenceType vertices[], int numVertices) {
  int i, padding;
  
  *fp = fopen("TRAVERSALS.txt", "w");

  padding = longestString(vertices, numVertices) + 3; // Aesthetics

  for (i=0; i<numVertices; i++) {
    printf("%-*s %d\n", padding, vertices[i].vertexID, vertices[i].degree); // DEBUGGING
    fprintf(*fp, "%-*s %d\n", padding, vertices[i].vertexID, vertices[i].degree);
  }

  fclose(*fp);
}