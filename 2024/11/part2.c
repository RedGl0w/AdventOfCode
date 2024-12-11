#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_s {
  long int value;
  struct node_s* next;
} node_t;

node_t* append(long int v, node_t* tail) {
  node_t* head = malloc(sizeof(node_t));
  head->value = v;
  head->next = tail;
  return head;
}

long int list_length(node_t* l) {
  long int counter = 0;
  while(l) {
    l = l->next;
    counter++;
  }
  return counter;
}

int int_length(long int i) {
  int sum = 1;
  while (i>9) {
    sum++;
    i /= 10;
  }
  return sum;
}

long int int_pow(int base, int power) {
  long int result = 1;
  while (power > 0) {
    if (power % 2 == 0) {
      power /= 2;
      base *= base;
    } else {
      power -= 1;
      result *= base;
      power = power / 2;
      base *= base;
    }
  }
  return result;
}

void split(long int value, int index, long int* a, long int* b) {
  long int p = int_pow(10, index);
  *a = value/p;
  *b = value%p;
}

void blink(node_t* l) {
  while(l) {
    if (l->value == 0) {
      l->value = 1;
    } else {
      int len = int_length(l->value);
      if ((len % 2) == 0) {
        long int a, b;
        split(l->value, len/2, &a, &b);
        l->value = a;
        node_t* next = append(b, l->next);
        l->next = next;
        l = next;
      } else {
        l->value *= 2024;
      }
    }
    l = l->next;
  }
}

node_t* load(const char* filename) {
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  node_t* head = NULL;
  node_t* tail = NULL;
  char c;
  int v = 0;
  while ((c = fgetc(f)) != '\n') {
    if (c == ' ') {
      if (head) {
        tail->next = append(v, NULL);
        tail = tail->next;
      } else {
        head = append(v, NULL);
        tail = head;
      }
      v = 0;
    } else {
      v *= 10;
      v += c - '0';
    }
  }
  tail->next = append(v, NULL);
  fclose(f);
  return head;
}

void print_list(node_t* l) {
  while(l) {
    printf("%ld ", l->value);
    l = l->next;
  }
  printf("\n");
}

void free_list(node_t* l) {
  while (l) {
    node_t *next = l->next;
    free(l);
    l = next;
  }
}

void blink_n_time(node_t* l, int n) {
  for (int i = 0; i < n; i++) {
    printf("\r%d", i);
    fflush(NULL);
    blink(l);
  }
  printf("\n");
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage : %s input.txt\n", argv[0]);
    exit(-1);
  }
  node_t* input = load(argv[1]);
  // print_list(input);
  blink_n_time(input, 75);
  // print_list(input);
  printf("Number of stones : %ld\n", list_length(input));
  free_list(input);
}
