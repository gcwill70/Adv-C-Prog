#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

#ifndef STACK_OFF
#define STACK_OFF
void insert(Node** cur, float val) {
	if (cur == NULL) {return;}
	Node* tmp = *cur;
	*cur = malloc(sizeof(Node));
	(*cur)->val = val;
	(*cur)->next = tmp;
	return;
}

bool removeNode(Node ** cur) {
	if (cur == NULL || *cur == NULL) {return false;}
	Node* toRemove = *cur;
	*cur = toRemove->next;
	free(toRemove);
	return true;
}

float pop(Stack* s) { //need to check if stack is empty before calling
	float ret = s->top->val;
	removeNode(&(s->top));
	return ret;
}

void push(Stack * s, float val) {
	insert(&(s->top), val);
}

bool twoNodes(Stack* s) { //check if there are at least two nodes in the stack
	if (s == NULL || s->top == NULL || s->top->next == NULL) {return false;}
	return true;
}

void freeStack(Stack* s) {
	while(removeNode(&(s->top))) {}
	return;
}

#endif
