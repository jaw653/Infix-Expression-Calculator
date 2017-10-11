#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "char.h"
#include "stack.h"
#include "scanner.h"
#include "string.h"
#include "cda.h"
#include "queue.h"

//Question: do we need to account for if the input is nums instead of vars?

bool is_operand(char *);
int determine_precedence(char *, char *);
void convertToPostfix(QUEUE *);

static void readInFile(FILE *, QUEUE *);    //Reads in file to queue


int main(int argc, char *argv[]) {
  FILE *fp = fopen(argv[1], "r");
  QUEUE *queue = newQUEUE(displaySTRING);

  readInFile(fp, queue);

  convertToPostfix(queue);
  printf("\n");
  return 0;
}

static void readInFile(FILE *fp, QUEUE *queue) {
  char *str = readToken(fp);

  /* While there's still more to read in the file */
  while (str) {
    enqueue(queue, newSTRING(str));
    str = readToken(fp);
  }
}



int priorityOf(char c) {
  switch (c) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;

    case '%':
      return 3;
    case '^':
      return 4;
  }
  return -1;
}

void convertToPostfix(QUEUE *queue) {
  STACK *stack = newSTACK(displaySTRING);
  char x;
  char *s;
  char c;

  while (sizeQUEUE(queue) > 0) {
    s = getSTRING(dequeue(queue));
    c = *s;

    if (isalnum(c)) printf("%c ", c);
    else {
      if (sizeSTACK(stack) > 0) {
        char s1 = *getSTRING(peekSTACK(stack));
        while (priorityOf(c) <= priorityOf(s1)) {
          x = *getSTRING(pop(stack));
          printf("%c ", x);
          if (sizeSTACK(stack) == 0) break;
          s1 = *getSTRING(peekSTACK(stack));
        }
      }
      push(stack, newSTRING(s));

    }
  }

  while (sizeSTACK(stack) > 0) {
    x = *getSTRING(pop(stack));
    printf("%c ", x);
  }
}
