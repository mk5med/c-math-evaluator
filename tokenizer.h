#ifndef TOKENIZER_H
#define TOKENIZER_H
/**
 * @brief Given a pointer to a string, return the next mathematical operator or number.
 * 
 * @param str_pointer Mutable pointer to the original string.
 * @param IS_NUMBER Mutable flag pointer to indicate if the result is a number.
 * @param IS_EOL Mutable flag pointer to indicate if the end of line has been reached.
 * @return int The current character or number read from input
 */
int tokenize(char **str_pointer, char *IS_NUMBER, char *IS_EOL);

#endif