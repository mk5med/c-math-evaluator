#include <stdio.h>
#include <stdlib.h>

int is_number(char val)
{
  return '0' <= val && val <= '9';
}

int is_not_control_char(int val)
{
  return val != '+' && val != '-' && val != '/' && val != '*';
}

int is_control_char(int val)
{
  return !is_not_control_char(val);
}

/**
 * @brief Given a pointer to a string, return the next mathematical operator or number.
 * 
 * @param str_pointer Mutable pointer to the original string.
 * @param IS_NUMBER Mutable flag pointer to indicate if the result is a number.
 * @param IS_EOL Mutable flag pointer to indicate if the end of line has been reached.
 * @return int The current character or number read from input
 */
int tokenize(char **str_pointer, char *IS_NUMBER, char *IS_EOL)
{
  char *buffer = calloc(10, sizeof(char));
  char *c = buffer;
  if (is_control_char(**str_pointer))
  {
    *IS_NUMBER = 0;
    char _c = **str_pointer; // Save the current character
    (*str_pointer)++;        // Increment the pointer reference to the next line
    if (*str_pointer == '\0')
      *IS_EOL = 1;
    else
      *IS_EOL = 0;
    return _c;
  }

  while (**str_pointer != '\0' && is_number(**str_pointer))
  {
    *c = **str_pointer;
    c++;
    (*str_pointer)++;
  }

  *IS_NUMBER = 1;
  if (**str_pointer == '\0')
    *IS_EOL = 1;
  else
    *IS_EOL = 0;

  return atoi(buffer);
}