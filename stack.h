/*Author: Jake Wachs (Credit: Dr. J. Lusth)
 *Date: 08/26/17
 *University of Alabama
 *
 *This file serves as the header for the stack.c file
 */

#ifndef __STACK_INCLUDED__
#define __STACK_INCLUDED__

#include <stdio.h>
#include "da.h"

typedef struct stack STACK;

extern STACK *newSTACK(void (*d)(FILE *,void *));
extern void push(STACK *items,void *value);
extern void *pop(STACK *items);
extern void *peekSTACK(STACK *items);
extern int sizeSTACK(STACK *items);
extern void displaySTACK(FILE *,STACK *items);
extern void visualizeSTACK(FILE *,STACK *items);

#endif
