#ifndef STACK_H
#define STACK_H

struct struct_Stack
{
  int length;
  int index;
  void **stackLocation;
  unsigned long data_size;
};

typedef struct struct_Stack Stack;
Stack *stack_create(unsigned long data_size);

void* stack_peek(Stack *stack);
void *stack_pop(Stack *stack);
void stack_push(Stack *stack, void *data);

#endif