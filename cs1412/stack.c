//
//  stackadt.c
//  
//  Created by Ryan Kelley on 4/26/17.
// 	Implementation of Stack in C.
//

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct node {
	int num;
	struct node *next;
} Node;

typedef struct StackHead {
	Node *head;
} *Stack;

/* Creates a stack */
Stack create(void) {
	Stack s = malloc(sizeof(Stack));
	if (s == NULL) {
		puts("[Err] Failed to create stack. Allocation error!");
		return NULL;
	} else {
		s->head = NULL;
		return s;
	}
} 

/* Pushes a number to the head of the stack */
void push(Stack s, int num) {
	Node *tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) {
		puts("[Err] Fatal error! Failed memory allocation.");
		exit(0);
	}
	// Setup temp with new data
	tmp->num = num;
	tmp->next = s->head;
	// Point StackHead to temp
	s->head = tmp;
}

/* Pops a number off the stack */
int pop(Stack s) {
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp = s->head;
	int popNum = tmp->num;
	// Moves head to the next node
	s->head = tmp->next;
	free(tmp);
	return popNum;
}

// Checks whether a stack is empty
int is_empty(Stack s) {
	return s->head == NULL;
}

/* Empties the stack */
int empty(Stack s) {
	int n = 0;
	while (s->head != NULL) {
		pop(s);
		n++;
	}
	return n;
}

void destroy(Stack s) {
	empty(s);
	free(s);
}
