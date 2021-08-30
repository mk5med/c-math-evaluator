#include <stdio.h>
#include <stdlib.h>
#include "./parser.h"
#include "./stack.h"
#include "./tokenizer.h"

// #define DEBUG

enum Math_Expression_Type
{
  Math_Operator,
  Math_Number
};

struct struct_Math_Expression
{
  enum Math_Expression_Type type;
  int value;
  struct struct_Math_Expression *left;
  struct struct_Math_Expression *right;
};

typedef struct struct_Math_Expression Math_Expression;

/**
 * @brief Helper method to print the current node tree. Traversal is made in an inorder depth-first format.
 * 
 * @param curr 
 * @param count 
 */
void print_expression(Math_Expression *curr, int count)
{
  if (curr == NULL)
  {
    for (int i = 0; i < count; i++)
      putchar('\t');
    printf("NULL\n");
    return;
  }

  if (curr->type == Math_Number)
  {
    for (int i = 0; i < count; i++)
      putchar('\t');
    printf("%d\n", curr->value);
    return;
  }

  print_expression(curr->left, count + 1);

  for (int i = 0; i < count; i++)
    putchar('\t');

  printf("(%c)\n", curr->value);
  print_expression(curr->right, count + 1);
}

/**
 * @brief Create an expression object.
 * 
 * @param type The type of the expression. Can be an operator or a number.
 * @param value The value to store into the node.
 * @return Math_Expression* 
 */
Math_Expression *create_expression(enum Math_Expression_Type type, int value)
{
  struct struct_Math_Expression *temp = malloc(sizeof(struct struct_Math_Expression));
  temp->type = type;
  temp->value = value;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

int is_composable(int val)
{
  return val == '*' || val == '/';
}

/**
 * @brief Insert a right child to the current node. This shifts any existing 'right' children down to the child
 * 
 * @param root 
 * @param value 
 */
void insert_right(Math_Expression *root, Math_Expression *value)
{
  Math_Expression *right_child = root->right;
  root->right = value;
  value->left = right_child;
}

/**
 * @brief Insert a left child to the current node. This shifts any existing 'left' children down to the child.
 * 
 * @param root 
 * @param value 
 */
void insert_left(Math_Expression *root, Math_Expression *value)
{
  Math_Expression *left_child = root->left;
  root->left = value;
  value->right = left_child;
}

/**
 * @brief Safely insert a math expression into the Math_Expression tree
 * 
 * @param root 
 * @param value 
 */
void insert_expression(Math_Expression *root, Math_Expression *value)
{
  if (root->left == NULL)
    insert_left(root, value);
  else if (root->right == NULL)
    insert_right(root, value);
  else // Case 3: Both paths are filled
  {
    // NOP
    if (value->type == Math_Number)
      printf("No space to insert (%d). Current layout: \n", value->value);
    else
      printf("No space to insert (%c). Current layout: \n", value->value);

    print_expression(root, 1);
  }
}

/**
 * @brief A recursive function to evaluate a mathematical expression tree.
 * 
 * @param node 
 * @return int 
 */
int eval_recursive(struct struct_Math_Expression *node)
{
  if (node == NULL)
  {
    printf("NULL DETECTED IN EVALUATION\n");
    return 0;
  }
  if (node->type == Math_Number)
  {
    return node->value;
  }

  int sum = eval_recursive(node->left);
  int val_right = eval_recursive(node->right);

  switch (node->value)
  {
  case '+':
    sum += val_right;
    break;
  case '-':
    sum -= val_right;
    break;
  case '/':
    sum /= val_right;
    break;
  case '*':
    sum *= val_right;
    break;
  default:
    break;
  }

  return sum;
}

/**
 * @brief Given a string math expression, evaluate and return the response.
 * 
 * @param str 
 * @return int 
 */
int solve(char *str)
{
  Stack *node_stack = stack_create(sizeof(Math_Expression));

  // Initialise the tree with a trivial addition to simplify the parsing logic
  Math_Expression *root = create_expression(Math_Operator, '+');
  root->left = create_expression(Math_Number, 0);
  stack_push(node_stack, root);

  Math_Expression *curr = root;

  char IS_NUMBER = 0;
  char IS_EOL = 0;
  char *str_pointer = str;

  while (IS_EOL == 0)
  {
    int value = tokenize(&str_pointer, &IS_NUMBER, &IS_EOL);
    if (IS_NUMBER == 1)
    {

#ifdef DEBUG
      printf("Case 1.1 '%d'\n", value);
#endif

      // Case 1.1: Add a numeric node to the right of contextual root
      insert_right(curr, create_expression(Math_Number, value));
      stack_push(node_stack, curr->right);
      curr = stack_peek(node_stack);
    }
    else // The current value is an operator
    {
      Math_Expression *operator= create_expression(Math_Operator, value);

      const char is_curr_number = curr->type == Math_Number;
      const char is_curr_operator = !is_curr_number;
      const char is_curr_operator_and_upcoming_negative = !is_curr_number && operator->value == '-';

      if (is_curr_number) // Always true unless an operator follows another operator
      {
        stack_pop(node_stack);                            // Remove the numeric node from the context stack
        Math_Expression *parent = stack_peek(node_stack); // Get the parent operator

        if (is_composable(operator->value))
        {
#ifdef DEBUG
          printf("Case 2.1\n");
#endif
          insert_right(parent, operator);
        }
        else // Move out of the context until root is reached or until a bracket is reached (TODO)
        {
#ifdef DEBUG
          printf("Case 2.2\n");
#endif

          Math_Expression *root;
          while (node_stack->index != 0)
            root = stack_pop(node_stack);
          operator->left = root;
          stack_push(node_stack, operator);
        }

        stack_push(node_stack, operator);
        curr = operator;
      }

      if (is_curr_operator)
      {
#ifdef DEBUG
        printf("Case 3\n");
#endif
        insert_right(curr, operator);
        insert_left(operator, create_expression(Math_Number, 0));
        curr = operator;
      }
    }
  }

  root = node_stack->stackLocation[0];

#ifdef DEBUG
  printf("Finally evaluating the expression.\n");
  printf("The current root: '%c'\n", root->value);
  print_expression(root, 0);
#endif
  return eval_recursive(root);
}