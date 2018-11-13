#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

Stack StackCreate(int size)
{
	int **data = (int **)malloc(sizeof(int *) * size);
	for (int i = 0; i < size; i++)
	{
		*(data + i) = (int *)malloc(sizeof(int) * 2);
	}

	Stack stack;
	stack.size = size;
	stack.top = -1;
	stack.stack = data;
	return stack;
}

int IsStackFull(Stack *stack)
{
	return stack->top == stack->size;
}

int IsStackEmpty(Stack *stack)
{
	return stack->top == -1;
}

int* PeekStack(Stack *stack)
{
	return stack->stack[stack->top];
}

int *StackPop(Stack *stack)
{
	if(!IsStackEmpty(stack))
	{
		int* value = stack->stack[stack->top];
		stack->top -= 1;
		return value;
	}

	return (int*) -1;
}

void StackPush(Stack *stack, int* data)
{
	if(!IsStackFull(stack))
	{
		stack->top += 1;
		stack->stack[stack->top] = data;
	}
}