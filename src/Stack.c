#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "Stack.h"

void StackCreate(Stack *stack, int size)
{
	Coord *data;
	data = (Coord *)malloc(sizeof(Coord) * size);

	stack->size = size;
	stack->top = -1;
	stack->stack = data;
}

void StackDestroy(Stack *stack)
{
	free(stack->stack);
}

int IsStackFull(Stack *stack)
{
	return stack->top >= stack->size - 1;
}

int IsStackEmpty(Stack *stack)
{
	return stack->top < 0;
}

Coord StackPeek(Stack *stack)
{
	return stack->stack[stack->top];
}

Coord StackPop(Stack *stack)
{
	if(IsStackEmpty(stack))
	{
		errx(1, "Stack empty.");
	}
	return stack->stack[stack->top--];
}

void StackPush(Stack *stack, Coord element)
{
	if(IsStackFull(stack))
	{
		errx(1, "Stack full.");
	}
	stack->stack[++stack->top] = element;
}