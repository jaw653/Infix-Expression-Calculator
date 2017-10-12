/*
 * Author: Jake Wachs
 * Date: 9/20/2017
 * The University of Alabama
 *
 * Infix Expression Calculator
 */

//Question: might have to change some logic. the first else if might have to be altered bc maybe argv2 could be (incorrectly a file name)?
//Question: where should I define my comparator and display fcs? Cause Lusth said he'll be using different comparators but the BST takes a comparator as one of its params...
//Question: can -v be paired with other flags? right now if it came after another flag output might be wrong
//Question: where/how to make display and comparator if Lusth is gonna use his own too?
//Question: going to need to get all the way to last line before doing the postfix conversion

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "stack.h"
#include "bst.h"
#include "queue.h"
#include "integer.h"
#include "string.h"
#include "real.h"
#include "scanner.h"

/*
 * Notes:
 *       When you're inserting values into BST, you need to input the value as a real...
 *
 */

/***** Private functions *****/
static void readInFile(FILE *, QUEUE *);    //Reads in file to queue
static int priorityOf(char c);

/***** Public functions *****/
void populateBST(FILE *, BST *);              //Sends only key/val pairs to bst
void printInput(QUEUE *);                     //Prints out input (-i option)
void convertToPostfix(QUEUE *);
QUEUE *getLastLine(QUEUE *);                  //Returns queue containing last line
int processPostFix(QUEUE *queue, BST *tree);  //Calculate final postfix number
void displayPair(FILE *, void *, void *);

/******************************************************************************/
/*                                ---MAIN---                                  */
/******************************************************************************/
int main(int argc, char *argv[]) {
  /* If any of the commands are -v, print and exit */
  int i;
  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0) { printf("Jake Wachs\n"); return 0; }
  }


  /* If matilda comes w/ no arguments (filenames or opts) */
  if (argc == 1) { return 0; }

  char *name = argv[argc - 1];
  FILE *fp1 = fopen(name, "r");

  BST *tree = newBST(displayPair, compareSTRING);
  populateBST(fp1, tree);

  if (fp1 != NULL) fclose(fp1);

  /* Else run through and complete all command line opts */
  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-b") == 0) {
      char *filename = argv[argc - 1];
      FILE *fp = fopen(filename, "r");

      QUEUE *queue = newQUEUE(displaySTRING);
      readInFile(fp, queue);
      //displayBST();

      if (fp != NULL) fclose(fp);
    }
    else if (strcmp(argv[i], "-i") == 0) {
      char *filename = argv[argc - 1];
      FILE *fp = fopen(filename, "r");

      QUEUE *queue = newQUEUE(displaySTRING);
      readInFile(fp, queue);
      printInput(queue);

      if (fp != NULL) fclose(fp);
    }
    else if (strcmp(argv[i], "-p") == 0) {
      char *filename = argv[argc - 1];
      FILE *fp = fopen(filename, "r");

      QUEUE *queue = newQUEUE(displaySTRING);
      readInFile(fp, queue);

      QUEUE *lastLine = getLastLine(queue);
      convertToPostfix(lastLine);

      if (fp != NULL) fclose(fp);
    }
  }

  /* Calculate final postfix number and print it */
  //processPostFix(queue, tree);

  return 0;
}
/******************************************************************************/
/******************************************************************************/

/*************** Private functions ***************/
static void readInFile(FILE *fp, QUEUE *queue) {
  char *str = readToken(fp);

  /* While there's still more to read in the file */
  while (str) {
    enqueue(queue, newSTRING(str));
    str = readToken(fp);
  }
}

/*************** Public functions **************/
/*
void runBOpts(BST *tree) {
//  print binary search tree (should be as simple as using displayBST)

}
*/

void populateBST(FILE *fp, BST *tree) {
  char *str = readToken(fp);
  while (str) {
    if (strcmp(str, "var") == 0) {
      char *s = readToken(fp);
      STRING *key = newSTRING(s);

      readToken(fp);

      char *x = readToken(fp);
      int i = atoi(x);
      double db = (double) i;
      REAL *value = newREAL(db);

      printf("inserting...\n");
      insertBST(tree, key, value);
    }

    str = readToken(fp);
  }
//  printf("displaying tree:\n");
//  displayBST(fp, tree);
}

void printInput(QUEUE *queue) {
  //print each token in the queue, printing newlines after ';'
  int i;
  int size = sizeQUEUE(queue);
  for (i = 0; i < size; i++) {
    STRING *x;

    //FIXME: possibly should be display real...tf, do I have to convert string to real?
    if (sizeQUEUE(queue) > 0) {
      x = dequeue(queue);
      displaySTRING(stdout, x);
    }

    if (strcmp(getSTRING(x), ";") == 0) printf("\n");
    else { printf(" "); }
  }

  //FIXME: should this newline be here?
//  printf("\n");
}

static int priorityOf(char c) {
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
  char *s;
  char c;

  while (sizeQUEUE(queue) > 0) {
    s = getSTRING(dequeue(queue));
    c = *s;

    if (isalnum(c)) printf("%c ", c);
    else if (c == '(') { push(stack, newSTRING(s)); }
    else if (c == ')') {
      if (sizeSTACK(stack) > 0) {
        char topStack = *getSTRING(peekSTACK(stack));
        while (topStack != '(') {
          printf("%c ", topStack);
          if (sizeSTACK(stack) == 0) break;
          pop(stack);
          topStack = *getSTRING(peekSTACK(stack));
        }
        pop(stack);
      }
    }
    else {
      if (sizeSTACK(stack) > 0) {
        char topStack = *getSTRING(peekSTACK(stack));
        while (priorityOf(c) <= priorityOf(topStack) && topStack != '(') {
          printf("%c ", topStack);
          pop(stack);
          if (sizeSTACK(stack) == 0) break;
          topStack = *getSTRING(peekSTACK(stack));
        }
      }
      push(stack, newSTRING(s));

    }
  }

  while (sizeSTACK(stack) > 0) {
    char topStack = *getSTRING(peekSTACK(stack));
    printf("%c ", topStack);
    pop(stack);
  }

  printf("\n");
}

QUEUE *getLastLine(QUEUE *queue) {
  STACK *fullStack = newSTACK(displaySTRING);
  STACK *smallStack = newSTACK(displaySTRING);
  QUEUE *lastLine = newQUEUE(displaySTRING);

  while (sizeQUEUE(queue) > 0) {
    push(fullStack, dequeue(queue));
  }

  pop(fullStack);

  while (sizeSTACK(fullStack) > 0) {
    char *s = getSTRING(peekSTACK(fullStack));
    char c = *s;
    if (c == ';') break;
    push(smallStack, pop(fullStack));
  }

  while (sizeSTACK(smallStack) > 0) {
    if (sizeSTACK(smallStack) == 0) break;
    enqueue(lastLine, pop(smallStack));
  }

  return lastLine;
}

int processPostFix(QUEUE *queue, BST *tree) {
  //calculate the final answer of the postfix expression using the bst when need be
}

void displayPair(FILE *fp, void *key, void *value) {
  displaySTRING(fp, key);
  fprintf(fp, "=");
  displayREAL(fp, value);
}
