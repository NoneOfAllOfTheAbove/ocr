#ifndef STACK_H
#define STACK_H

typedef struct Stack Stack;
struct Stack
{
	int size;
	int top;
	int** stack;
};

Stack StackCreate(int size);
int IsStackFull(Stack *stack);
int IsStackEmpty(Stack *stack);
int *PeekStack(Stack *stack);
int *StackPop(Stack *stack);
void StackPush(Stack *stack, int *data);

#endif