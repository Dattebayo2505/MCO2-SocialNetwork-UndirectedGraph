#define MAX_FILENAME_LENGTH 20
#define MAX_NAMELENGTH      31
#define MAX_VERTICES        20

typedef char stringNames[31];

typedef struct SequenceTag {
  stringNames vertexID;
  char neighbors[MAX_VERTICES][MAX_NAMELENGTH]; // adjacent vertices to the vertexID
  char adjMatrixRow[MAX_VERTICES];
  int degree;
  int neighborTotal;
  int originalRank;

} SequenceType;

// graph.c
void resetArray(char input[], int size);
void toLowerCase(char str[]);
void getNumVertices(FILE **fp, int *numVertices);
void sortNeighbors(char neighbors[][MAX_NAMELENGTH], int neighborTotal);
void swapSequenceType(SequenceType *a, SequenceType *b);
void sortVertices(SequenceType vertices[], int numVertices);
void readInput(FILE **fp, SequenceType vertices[], int numVertices);
int isValidName(SequenceType vertices[], int numVertices, char inputName[]);
int startIndex(SequenceType vertices[], int numVertices);
void printGraph(SequenceType vertices[], int numVertices);
void createAdjMatrix(SequenceType vertices[], int numVertices);
int longestString(SequenceType vertices[], int numVertices);
int print(SequenceType vertices[], int numVertives);
void printVertexDegrees(FILE **fp, SequenceType vertices[], int numVertices);

// traversals.c
void DFS(int vertex, SequenceType vertices[], int numVertices, 
         int visited[], char dfsSequence[][MAX_NAMELENGTH]);
void BFS(int vertex, SequenceType vertices[], int numVertices, 
         int visited[], char bfsSequence[][MAX_NAMELENGTH]);
void printTraversalsToFile(FILE **fp, SequenceType vertices[], int numVertices, 
                           char bfsSequence[][MAX_NAMELENGTH], 
                           char dfsSequence[][MAX_NAMELENGTH]);