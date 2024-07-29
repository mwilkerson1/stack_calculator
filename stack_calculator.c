#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Stack
{
    char operator;          // Operator (+, -, *, /) or '\0' for operand
    float operand;          // Operand value
    struct Stack *next;     // Pointer to the next node in the stack
} Stack;

Stack* create_node(char, float);        // Function to create a new stack node
Stack* push(Stack*, char, float);       // Function to push a node onto the stack
Stack* pop(Stack *);                    // Function to pop a node from the stack

void infix_to_postfix(const char*, char*);    // Function to convert infix expression to postfix
float evaluate_postfix(char*);                // Function to evaluate postfix expression
void print_stack(Stack *);                     // Function to print the stack

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("No argument passed.\n");
        return 0;
    }
    else
    {
        char *infix = argv[1];       // Get the infix expression from command line argument
        char postfix[25];            // Array to store the postfix expression
        
        infix_to_postfix(infix, postfix);    // Convert infix to postfix
        
        float result = evaluate_postfix(postfix);    // Evaluate the postfix expression

        printf("%f\n", result);     // Print the result
    }

    return 0;
}

Stack* create_node(char operator, float operand)
{
    Stack* new_node = (Stack*)malloc(sizeof(Stack));    // Allocate memory for new node
    if (!new_node)
    {
        printf("Error: Memory allocation failed.\n");
    }
    else
    {
        new_node->operator = operator;      // Set the operator
        new_node->operand = operand;        // Set the operand
        new_node->next = NULL;              // Set the next pointer to NULL
        return new_node;
    }
}

Stack* push(Stack *top, char operator, float operand)
{
    Stack *new_node = create_node(operator, operand);    // Create a new node
    if (top == NULL)
    {
        top = new_node;     // If stack is empty, make the new node as top
    }
    else
    {
        new_node->next = top;    // Set the next pointer of new node to current top
        top = new_node;          // Make the new node as top
    }
    return top;
}

Stack* pop(Stack *top)
{
    if (top == NULL)
    {
        printf("Stack is empty.\n");
    }
    else
    {
        Stack *ptr = top;       // Store the current top node
        top = top->next;        // Move the top pointer to the next node
        free(ptr);              // Free the memory of the previous top node
    }
    return top;
}

void infix_to_postfix(const char *infix, char *postfix) {
    Stack *top = NULL;      // Initialize an empty stack
    int i = 0;
    int j = 0;

    while (infix[i] != '\0') 
    {
        if (isdigit(infix[i])) 
        {
            while (isdigit(infix[i])) 
            {
                postfix[j++] = infix[i++];    // Copy the digits to postfix expression
            }
            postfix[j++] = ' ';     // Add a space after each operand
        } 
        else if (infix[i] == '*' || infix[i] == '/') 
        {
            while (top != NULL && (top->operator == '*' || top->operator == '/')) 
            {
                postfix[j++] = top->operator;   // Pop operators with higher precedence and add them to postfix
                postfix[j++] = ' ';
                top = pop(top);
            }
            top = push(top, infix[i++], -1);    // Push the current operator onto the stack
        } 
        else if (infix[i] == '+' || infix[i] == '-') 
        {
            while (top != NULL && (top->operator == '+' || top->operator == '-' || top->operator == '*' || top->operator == '/')) 
            {
                postfix[j++] = top->operator;   // Pop operators with higher or equal precedence and add them to postfix
                postfix[j++] = ' ';
                top = pop(top);
            }
            top = push(top, infix[i++], -1);    // Push the current operator onto the stack
        } 
        else if (isspace(infix[i])) 
        {
            i++;    // Ignore whitespace characters
        } 
        else 
        {
            printf("Error: %c is neither an operator nor operand.\n", infix[i]);
            exit(1);
        }
    }

    while (top != NULL) {
        postfix[j++] = top->operator;   // Pop remaining operators from the stack and add them to postfix
        postfix[j++] = ' ';
        top = pop(top);
    }

    postfix[j] = '\0';     // Add null terminator to the postfix expression
}

float evaluate_postfix(char *postfix)
{
    Stack *top = NULL;      // Initialize an empty stack
    int i = 0;
    while (postfix[i] != '\0')
    {
        if (isdigit(postfix[i]))
        {
            int num = 0;
            while(isdigit(postfix[i]))
            {
                num = num * 10 + (postfix[i++] - '0');    // Convert digits to integer
            }
            top = push(top, '\0', (float)num);    // Push the operand onto the stack
        }
        else if (isspace(postfix[i]))
        {
            i++;    // Ignore whitespace characters
        }
        else
        {
            float operand2 = top->operand;   // Get the second operand from the stack
            top = pop(top);
            float operand1 = top->operand;   // Get the first operand from the stack
            top = pop(top);
            float result;
            switch(postfix[i])
            {
                case '+': result = operand1 + operand2; break;    // Perform the operation based on the operator
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                default: 
                    printf("Error: invalid operator %c\n", postfix[i]);
                    exit(1);
            }
            top = push(top, '\0', result);    // Push the result onto the stack
            i++;
        }
    }
    float final_result = top->operand;      // Get the final result from the stack
    top = pop(top);

    while (top != NULL)
    {
        top = pop(top);     // Pop remaining nodes from the stack
    }

    return final_result;    // Return the final result
}

void print_stack(Stack *top)
{
    if (top == NULL)
    {
        printf("Stack is empty.\n");
    }
    else
    {
        Stack* ptr = top;
        while (ptr != NULL)
        {
            if (ptr->operator == '\0')
            {
                printf("%f -> ", ptr->operand);     // Print operand
            }
            else
            {
                printf("%c -> ", ptr->operator);     // Print operator
            }
            ptr = ptr->next;
        }
        printf("NULL\n");
    }
}
