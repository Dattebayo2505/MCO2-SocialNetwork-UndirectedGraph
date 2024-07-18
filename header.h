#define MAX_FILENAME_LENGTH 20
#define MAX_NAMELENGTH 31
#define MAX_VERTICES 20 // as stated by Sir
#define MAX_LINE 150 // might change to malloc soon

typedef char string150[MAX_LINE];
typedef char stringNames[31];

typedef struct SequenceTag {
  stringNames vertexID;
  char neighbors[19][MAX_NAMELENGTH]; // adjacent vertices to the vertexID
  char adjMatrixRow[MAX_VERTICES];
  int degree;
  int neighborTotal;

} SequenceType;