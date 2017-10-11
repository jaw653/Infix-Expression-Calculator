#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "char.h"

struct CHAR {
  char value;
};

CHAR *newCHAR(char c) {
  CHAR *p = malloc(sizeof(CHAR));
  assert(p != 0);
  p->value = c;
  return p;
}

char getCHAR(CHAR *c) {
  return c->value;
}

char setCHAR(CHAR *c, char x) {
  char old = c->value;
  c->value = x;
  return old;
}

void displayCHAR(FILE *fp, void *c) {
  fprintf(fp, "%c", getCHAR((CHAR *) c));
}

void freeCHAR(CHAR *c) {
  free(c);
}
