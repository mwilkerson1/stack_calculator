# Stack Calculator

A simple stack-based calculator implemented in C that converts infix expressions to postfix and evaluates them.

## Features

- Converts infix expressions to postfix notation
- Evaluates postfix expressions
- Handles multi-digit numbers and basic arithmetic operators (+, -, *, /)

## Usage

### Compilation

Compile the program using `gcc`:

```sh
gcc -o stack_calculator stack_calculator.c
```
### Runing the program

To run the program, pass an infix expression as a command-line argument (note: current version does not handle floats as inputs)

```sh
./stack_calculator "3+5*2"
# Output: 13.000000
```