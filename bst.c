/*
 * Author: Jake Wachs
 * Date: 9/20/2017
 * The University of Alabama
 *
 * Below is the implementation of the header file bst.h, created by
 * Dr. John Lusth
 *
 * Question(s):
 *           For findBST, are we looking for the variable name or the value?
 *           Spaces for displayBST, where do they go?
 *           For findBST, are we assuming the value exists?
 *           Is my static declaration of printBST good?
 *           So I think my implementations of insert/find are good but my understanding of the testing is not...
 *
 * Notes: For recursion, may have to put if (left/right tree->ptr exist) to catch seg faults
 */

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "bst.h"
#include "string.h"

struct node {
  void *key;
  void *value;
  struct node *left;
  struct node *right;
};

struct BST {
  struct node *root;
  int size;                                 //Size of bst in nodes
  void (*display)(FILE *, void *, void *);  //Display function pointer
  int (*comparator)(void *, void *);        //Comparator function pointer
};

/******************** Private functions ********************/
static void *insertBSTHelper(struct node *root, BST *tree, void *key, void *value) {
    if (root == NULL) {
      assert(sizeof(struct node));

      root = (struct node *)malloc(sizeof(struct node));
      root->key = key;
      root->value = value;
      root->left = root->right = NULL;

      tree->size += 1;
      return root;
    }
    else if (tree->comparator(key, root->key) < 0) {
      root->left = insertBSTHelper(root->left, tree, key, value);
    }
    else {
      root->right = insertBSTHelper(root->right, tree, key, value);
    }

    return root;
}

static void *findBSTHelper(struct node *root, BST *tree, void *key) {
  /* Value found */
  if (root == NULL || tree->comparator(key, root->key) == 0) {
    if (root == NULL) return NULL;
    return root->value;
  }
  else if (tree->comparator(key, root->key) < 0) {
    return findBSTHelper(root->left, tree, key);
  }
  else {
    return findBSTHelper(root->right, tree, key);
  }
}

static void printInOrderTree(FILE *fp, struct node *root, BST *tree) {
  if (tree->size == 0) {
    printf("[]");
    return;
  }
  else {
    printf("[");
    if (root->left) printInOrderTree(fp, root->left, tree);

    if (root->left) printf(" ");
    tree->display(fp, root->key, root->value);
    if (root->right) { printf(" "); }

    if (root->right) printInOrderTree(fp, root->right, tree);
    printf("]");
  }
}


/************************* Public functions *************************/
BST *newBST(void (*display)(FILE *,void *,void *),int (*comparator)(void *,void *)) {
  assert(sizeof(BST) != 0);

  BST *tree = malloc( sizeof(BST) );

  tree->root = NULL;
  tree->size = 0;
  tree->display = display;
  tree->comparator = comparator;


  return tree;
}

void insertBST(BST *tree, void *key, void *value) {
  tree->root = insertBSTHelper(tree->root, tree, key, value);
}

void *findBST(BST *tree, void *key) {
  return findBSTHelper(tree->root, tree, key);
}

int sizeBST(BST *tree) {
  return tree->size;
}

void displayBST(FILE *fp, BST *tree) {
  printInOrderTree(fp, tree->root, tree);
}
