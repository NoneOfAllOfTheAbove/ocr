#ifndef STACK_H
#define STACK_H

typedef struct Coord Coord;
struct Coord
{
	int x;
	int y;
};

typedef struct Stack Stack;
struct Stack
{
	int size;
	int top;
	Coord* stack;
};

void StackCreate(Stack *stack, int size);
int IsStackFull(Stack *stack);
int IsStackEmpty(Stack *stack);
Coord StackPeek(Stack *stack);
Coord StackPop(Stack *stack);
void StackPush(Stack *stack, Coord element);

#endif