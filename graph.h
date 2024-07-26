#include <stdio.h>
#include <string.h>
#include <ctype.h>


/**
 * Helper Function
 * Resets the elements of the input array to zero.
 *
 * @param input The array to be reset.
 * @param size The size of the array.
 */
void resetArray(char input[], int size) { 
  memset(input, 0, size); 
}

/**
 * Helper Function
 * Converts a string to lowercase.
 *
 * This function converts a string to lowercase.
 *
 * @param str The string to be converted to lowercase.
 */
void toLowerCase(char str[]){
  int i;
  for (i=0; str[i]; i++){
    str[i] = tolower(str[i]);
  }
}

/**
 * Reads the number of vertices from a file.
 *
 * This function prompts the user for a filename, opens the file, 
 * and reads the number of vertices from it.
 * The number of vertices is stored in the variable pointed to by `numVertices`.
 *
 * @param fp A pointer to a file pointer.
 * @param numVertices A pointer to an integer where the number of vertices will be stored.
 */
void getNumVertices(FILE **fp, int *numVertices) {
  char filename[MAX_FILENAME_LENGTH];

  printf("Input filename: ");
  scanf("%s", filename); // Un-comment out
  printf("GRAPH.txt\n"); strcpy(filename, "GRAPH.txt"); // DEBUGGING
  *fp = fopen(filename, "r");

  if (*fp == NULL) {
    printf("%s not found.\n", filename);
    return;
  }
  else
    fscanf(*fp, "%d", numVertices);
}

/**
 * Helper Function
 * Sorts an array of strings in ascending order.
 *
 * This function takes an array of strings and sorts them in ascending order.
 *
 * @param neighbors The array of strings to be sorted.
 * @param neighborTotal The number of strings in the array.
 */
void sortNeighbors(char neighbors[][MAX_NAMELENGTH], int neighborTotal) {
  int i, j;
  char key[MAX_NAMELENGTH];

  for (i = 1; i < neighborTotal; i++){
      strcpy(key, neighbors[i]);
      j = i -1;

        while (j >= 0 && strcmp(neighbors[j], key) > 0){
          strcpy(neighbors[j + 1], neighbors[j]);
          j--;
    }
    strcpy(neighbors[j + 1], key);
  }
}

/**
 * Helper Function 
 * Swaps the values of two SequenceType variables.
 *
 * This function takes two pointers to SequenceType variables and swaps their values.
 *
 * @param a Pointer to the first SequenceType variable.
 * @param b Pointer to the second SequenceType variable.
 */
void swapSequenceType(SequenceType *a, SequenceType *b) {
  SequenceType temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * Helper Function
 * Sorts an array of vertices in ascending order based on their vertexID.
 *
 * @param vertices The array of vertices to be sorted.
 * @param numVertices The number of vertices in the array.
 */
void sortVertices(SequenceType vertices[], int numVertices) {
  int i, j;

  for (i = 1; i < numVertices; i++) {
    j = i - 1;
    while (j >= 0 && strcmp(vertices[j].vertexID, vertices[j + 1].vertexID) > 0) {
      swapSequenceType(&vertices[j], &vertices[j + 1]);
      j--;
    }
  }
}


/**
 * Reads the input from a file and stores it in an array of SequenceType structures.
 *
 * This function reads the input from a file and stores it in an array of SequenceType structures.
 *
 * @param fp A pointer to a file pointer.
 * @param vertices An array of SequenceType structures where the input will be stored.
 * @param numVertices The number of vertices in the vertices array.
 */
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
      vertices[vertexIDCtr].originalRank = vertexIDCtr;
      resetArray(temp, sizeof(stringNames));
      neighborCtr = 0;
      ++vertexIDCtr;
    }
  }
  fclose(*fp);
}

/**
 * Checks if the input name is present among the vertices stored.
 *
 * This function checks if the input name is a valid vertexID in the vertices array.
 * If the name is valid, the function returns the index of the vertex in the vertices array.
 * If the name is not valid, the function returns -1.
 *
 * @param vertices An array of SequenceType structures containing vertex information.
 * @param numVertices The number of vertices in the vertices array.
 * @param inputName The name to be checked.
 * @return The index of the vertex in the vertices array if the name is valid, -1 otherwise.
 */
int isValidName(SequenceType vertices[], int numVertices, char inputName[]) {
  int i;
  char tempArray[MAX_NAMELENGTH];
  char inputNameLower[MAX_NAMELENGTH];

  // Convert inputName to lowercase
  strncpy(inputNameLower, inputName, MAX_NAMELENGTH - 1);
  inputNameLower[MAX_NAMELENGTH - 1] = '\0';
  toLowerCase(inputNameLower);

  for (i = 0; i < numVertices; i++) {
    // Convert vertexID to lowercase
    strncpy(tempArray, vertices[i].vertexID, MAX_NAMELENGTH - 1);
    tempArray[MAX_NAMELENGTH - 1] = '\0';
    toLowerCase(tempArray);

    // Compare the lowercase versions
    if (strcmp(tempArray, inputNameLower) == 0)
      return i;
  }
  return -1;
}

/**
 * Prompts the user for a start vertex for the traversal.
 *
 * This function prompts the user for a start vertex for the traversal 
 * and returns the index of the vertex in the vertices array.
 *
 * @param vertices An array of SequenceType structures containing vertex information.
 * @param numVertices The number of vertices in the vertices array.
 * @return The index of the start vertex in the vertices array.
 */
int startIndex(SequenceType vertices[], int numVertices) {
  stringNames startVertex;
  int indexVertex;

  printf("Input start vertex for the traversal: ");
  scanf("%s", startVertex);

  indexVertex = isValidName(vertices, numVertices, startVertex);
  if (indexVertex == -1) {
    printf("Vertex %s not found.\n", startVertex);
    return -1;
  }

  return indexVertex;
}

// DEBUGGING ONLY
void printGraph(SequenceType vertices[], int numVertices) {
  for (int i=0; i<numVertices; i++) {
    for (int j=0; j<numVertices; j++) {
      printf("%d ", vertices[i].adjMatrixRow[j]);
    }
    printf("\n");
  }
  printf("\n");
}


/**
 * Creates an adjacency matrix for the given vertices in the graph.
 *
 * @param vertices An array of SequenceType representing the vertices in the graph.
 * @param numVertices The number of vertices in the graph.
 */
void createAdjMatrix(SequenceType vertices[], int numVertices) {

  int neighborCtr = 0, i, j;

  for (i = 0; i < numVertices; i++) {
    for (j = 0; j < numVertices; j++)
      vertices[i].adjMatrixRow[j] = 0;
  }

  for (i = 0; i < numVertices; i++) {
    sortNeighbors(vertices[i].neighbors, vertices[i].neighborTotal);
  }

  // DEBUGGING (Show vertexID along with neighbors)
  for (i = 0; i < numVertices; i++) {
    printf("%s ", vertices[i].vertexID);
    for (j = 0; j < vertices[i].neighborTotal; j++) {
      printf("%s ", vertices[i].neighbors[j]);
    }
    printf("\n");
  }

  for (i = 0; i < numVertices; i++) {
    vertices[i].degree = 0; // Initialize degree of vertex i to 0

    for (neighborCtr=0; neighborCtr<vertices[i].neighborTotal; neighborCtr++) { // Iterate over each neighbor of vertex i
      for (j=0; j<numVertices; j++) { // Compare with every other vertex
        if (strcmp(vertices[i].neighbors[neighborCtr], vertices[j].vertexID) == 0) { // If neighbor's ID matches vertex j's ID
          vertices[i].adjMatrixRow[j] = 1; // Update adjacency matrix
          ++vertices[i].degree; // Increment degree of vertex i
          break; // No need to continue this loop since match is found
        }
      }
    }
  }

  printGraph(vertices, numVertices); // DEBUGGING
}


/**
 * Finds the length of the longest string in the vertexID field of the vertices array.
 *
 * @param vertices An array of SequenceType structures containing vertex information.
 * @param numVertices The number of vertices in the vertices array.
 * @return The length of the longest vertexID string.
 */
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

/**
 * Finds the index of the vertex with the smallest originalRank in the vertices array.
 *
 * @param vertices An array of SequenceType structures containing vertex information.
 * @param numVertices The number of vertices in the vertices array.
 * @return The index of the vertex with the smallest originalRank.
 */
int print(SequenceType vertices[], int numVertives) {
  int i, minIndex;

  minIndex = 0;
  for (i=0; i<numVertives; i++) {
    if (vertices[i].originalRank < vertices[minIndex].originalRank) {
      minIndex = i;
    }
  }
  vertices[minIndex].originalRank = 100; // High enough to not be considered in the next iteration
  return minIndex;

}

/**
 * Prints the vertex degrees to the console and to a file.
 *
 * @param fp A pointer to the file to which the vertex degrees will be printed.
 * @param vertices An array of SequenceType structures containing vertex information.
 * @param numVertices The number of vertices in the vertices array.
 */
void printVertexDegrees(FILE **fp, SequenceType vertices[], int numVertices) {
  int i, original, padding;

  *fp = fopen("TRAVERSALS.txt", "w");

  padding = longestString(vertices, numVertices) + 3; // Aesthetics


  for (i=0; i<numVertices; i++) {
    original = print(vertices, numVertices);
    printf("%-*s %d\n", padding, vertices[original].vertexID, vertices[original].degree); // DEBUGGING
    fprintf(*fp, "%-*s %d\n", padding, vertices[original].vertexID, vertices[original].degree);
  }

  fclose(*fp);
}