#include <stdlib.h>
#include <stdio.h>
#include "./stack.h"

#define DEFAULT_STACK_SIZE 10

Stack *stack_create(unsigned long data_size)
{
  struct struct_Stack *temp = malloc(sizeof(struct struct_Stack));
  temp->length = DEFAULT_STACK_SIZE;
  temp->index = 0;
  temp->data_size = data_size;
  temp->stackLocation = calloc(DEFAULT_STACK_SIZE, data_size);
  return temp;
}

void* stack_pop(Stack *stack)
{
  void* obj = stack_peek(stack);
  stack->index--;
  return obj;
}

void stack_push(Stack *stack, void *data)
{
  if (stack->index == stack->length) // Capacity reached
  {
    // Double the stack size
    stack->length *= 2;
    stack->stackLocation = realloc(stack, stack->length * stack->data_size);
  }

  stack->stackLocation[stack->index] = data;
  stack->index++;
}

void* stack_peek(Stack *stack)
{
  if (stack->index <= 0)
  {
    printf("ERROR: Index out of bounds.\n");
    return NULL;
  }
  
  return stack->stackLocation[stack->index-1];
}