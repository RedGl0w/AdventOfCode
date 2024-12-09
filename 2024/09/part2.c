#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

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
  int* fromStart = disk + diskSize - 1;
  while (fromStart >= disk) {
    // printf("Start searching for file at %d\n", (int)(fromStart - disk));
    // printDisk(disk, diskSize);

    // We start by computing the file we would want to copy
    while(*fromStart == -1) {
      fromStart--;
    }
    int* fromEnd = fromStart;
    while(*fromEnd == *fromStart) {
      fromEnd--;
    }
    fromEnd++;

    // We now need to find if there is an empty space at its left available
    int *toStart = disk;
    int* toEnd = disk;
    bool found = false;
    while (toStart < fromEnd) {
      while (*toStart != -1 && toStart < fromEnd) {
        toStart++;
      }
      toEnd = toStart;
      while (*toEnd == -1 && toEnd < fromEnd) {
        toEnd++;
      }
      toEnd--;
      if (toEnd-toStart>=fromStart-fromEnd) {
        // We found an available space large enough
        found = true;
        break;
      }
      toStart++;
    }

    // If we couldn't find a space for the file, we continue with next file
    if (!found) {
      fromStart = fromEnd - 1;
      continue;
    }

    // We need to copy now the file
    // printf("%d %d %d %d\n", (int)(fromStart-disk), (int)(fromEnd-disk), (int)(toStart-disk), (int)(toEnd-disk));
    while (fromStart>=fromEnd) {
      *toStart = *fromStart;
      *fromStart = -1;
      toStart++;
      fromStart--;
    }
  }
}

long int checkSum(int* disk, int diskSize) {
  long int total = 0;
  for (int i = 0; i < diskSize; i++) {
    if (disk[i] == -1) {
      // Contrary to the first part, when we meet a .
      // we can't be sure to have explored the disk
      continue;
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
