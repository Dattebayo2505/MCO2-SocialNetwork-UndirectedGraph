void DFS(int vertex, SequenceType vertices[], int numVertices, 
         int visited[], char dfsSequence[][MAX_NAMELENGTH]);
void BFS(int vertex, SequenceType vertices[], int numVertices, 
         int visited[], char bfsSequence[][MAX_NAMELENGTH]);
void printTraversalsToFile(FILE **fp, SequenceType vertices[], int numVertices, 
                           char bfsSequence[][MAX_NAMELENGTH], 
                           char dfsSequence[][MAX_NAMELENGTH]);