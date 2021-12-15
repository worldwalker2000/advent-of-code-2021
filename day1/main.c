#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void solve_part_1(char* buffer)
{
  int prev = -1;
  int incs = 0;

  char* curr = strtok(buffer, "\n");
  while(curr != NULL) {
    if(prev == -1) {
      prev = atoi(curr);
    }
    else {
      int v = atoi(curr);
      if (v > prev) ++incs;
      prev = v;
    }

    curr = strtok(NULL, "\n");
  }

  printf("Number of increases: %d\n", incs);
}

void solve_part_2(char* buffer)
{
  int cap = 100;
  int size = 0;
  int* values = (int*) malloc(sizeof(int) * cap);

  char* curr = strtok(buffer, "\n");
  while(curr != NULL) {
    if(size >= cap) {
      cap += 100;
      values = (int*) realloc(values, sizeof(int) * cap);
    }
    values[size++] = atoi(curr);
    curr = strtok(NULL, "\n");
  }

  int incs = 0;
  for(int i = 0; i < size; ++i) {
    int sum1 = values[i] + values[i+1] + values[i+2];
    int sum2 = values[i+1] + values[i+1+1] + values[i+2+1];

    if(sum2 > sum1) incs++;

  }

  free(values);

  printf("Number of increases on sliding window: %d\n", incs);
}

int main(int argc, char** argv)
{
  (void) argc;
  argv++; // skip program path

  FILE* file = fopen(*argv, "r");
  if(file == NULL) {
    fprintf(stderr, "Failed to load file %s.\n", *argv);
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  unsigned long file_length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char* buffer = (char*) malloc(file_length + 1); // +1 for null terminator
  if(buffer == NULL) {
    fprintf(stderr, "Failed to make buffer for reading file %s.\n", *argv);
    exit(1);
  }

  if(fread(buffer, 1, file_length, file) != file_length) {
    fprintf(stderr, "Failed to read file %s.\n", *argv);
    exit(1);
  }

  buffer[file_length] = '\0'; // Add null terminator to end of buffer so it plays nice

  fclose(file);

  // strtok wrecks the string so only one can be uncomented at a time.
  //solve_part_1(buffer);
  solve_part_2(buffer);

  free(buffer);

  return 0;
}
