/*
 * Author: Jake Wachs
 * The purpose of this file is to test the BST, not the entire matilda thing
 */

#include <stdio.h>
#include "scanner.h"
#include "bst.h"
#include "integer.h"
#include "string.h"

static int personal_comparator(void *, void *);
static void personal_display(FILE *fp, void *key, void *value);

int main(void) {
  printf("Attempting to initialize...\n");
  BST *tree = newBST(personal_display, personal_comparator);
  printf("Tree successfully initialized.\n");

  printf("Attempting to insert into BST...\n");
  insertBST(tree, newINTEGER(1), newINTEGER(10));
  insertBST(tree, newINTEGER(2), newINTEGER(20));
  printf("Insert was successful.\n");

  printf("Attempting to find node with key val 1...\n");
  void *val = findBST(tree, newINTEGER(1));

	return 0;
}

static int personal_comparator(void *v1, void *v2) {
  STRING *v1_string = newSTRING( (char *)v1 );
  STRING *v2_string = newSTRING( (char *)v2 );

  if (getSTRING(v1_string) < getSTRING(v2_string)) return -1;
  else if (getSTRING(v1_string) > getSTRING(v2_string)) return 1;
  else { return 0; }
}

static void personal_display(FILE *fp, void *key, void *value) {
  fprintf(fp, "%p=%p", key, value);
}
