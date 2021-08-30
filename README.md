# C Math Expression Evaluator
This project aims solves the problem of mathematical expression evaluation from input strings.

In a high level, the program creates an in-memory binary tree representation of an input expression and evaluates the tree recursively from the root node. To support negative numbers the program automatically creates and inserts an expression to evaluate a subtraction from zero for the numeric context. For those who are interested, another way to implement the negative numbers is to create an expression to multiply the numeric context by -1. 

## Support
- Operations with integer values up to 10 digits.
- All fundemental mathematical operations (+, -, *, /).
- (Planned) Order of Operations with Braces.
- (Planned) Evaluating expressions with arbitrary input spacing.


## How to use the program
To run the tests you can simply compile and run the project.

The parsing logic can be used in other programs through the provided `int solve(char *str)` API which accepts a string and returns the evaluated integer result.

