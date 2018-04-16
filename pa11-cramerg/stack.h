#ifndef _STACK_H_
#define _STACK_H_

typedef struct Node {
        float val;
        struct Node* next;
}Node;

typedef struct Stack {
        Node* top;
}Stack;

bool removeNode(Node ** cur);
void insert(Node ** cur, float val);
void push(Stack * s, float val);
float pop(Stack * s);
bool twoNodes(Stack *s);
void freeStack(Stack* s);

#endif
