#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

bool digit(char c) {
  return '0' <= c && c <= '9';
}

int loadInput(const char* filename, int** input) {
  // We start by reading input file as string
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  fseek(f, 0, SEEK_END);
  size_t inputLength = ftell(f);
  fseek(f, 0, SEEK_SET);
  char* textInput = (char*) malloc(sizeof(char) * inputLength);
  fgets(textInput, inputLength, f);
  fclose(f);

  // We compute disk size
  int diskSize = 0;
  char *position = textInput;
  while (digit(*position)) {
    diskSize += *position - '0';
    position++;
  }

  // And we convert input as disk
  position = textInput;
  int *disk = malloc(sizeof(int) * diskSize);
  int id = 0;
  int *positionOnDisk = disk;
  bool isFile = true;
  while (digit(*position))
  {
    int blockSize = *position - '0';
    for (int i = 0; i < blockSize; i++) {
      *positionOnDisk = isFile ? id : -1;
      positionOnDisk++;
    }
    if (isFile) {
      id++;
    }
    isFile = !isFile;
    position++;
  }

  free(textInput);
  *input = disk;
  return diskSize;
}

void printDisk(int* disk, int diskSize) {
  for (int i = 0; i < diskSize; i++) {
    if (disk[i] == -1) {
      printf(".");
    } else {
      printf("%d", disk[i]);
    }
  }
  printf("\n");
}

void order(int* disk, int diskSize) {
  int* from = disk + diskSize - 1;
  int* to = disk;
  while (to < from) {
    //printDisk(disk, diskSize);
    if (*to != -1) {
      to++;
    } else if (*from == -1) {
      from--;
    } else {
      *to = *from;
      *from = -1;
      to++;
      from--;
    }
  }
}

long int checkSum(int* disk, int diskSize) {
  long int total = 0;
  for (int i = 0; i < diskSize; i++) {
    if (disk[i] == -1) {
      // We finished reading the disk (all the following
      // bytes should be -1 because it is ordered)
      break;
    }
    total += disk[i] * i;
  }
  return total;
}

int main() {
  int *disk;
  int diskSize = loadInput("input.txt", &disk);
  printDisk(disk, diskSize);
  order(disk, diskSize);
  printDisk(disk, diskSize);
  printf("Checksum : %ld\n", checkSum(disk, diskSize));
}
