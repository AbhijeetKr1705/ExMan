#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

// Function to return precedence of operators
int precedence(char operator)
{
    switch (operator)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return -1;
    }
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Main functio to convert infix expression
// to postfix expression
void infixToPostfix(char infix[])
{
    int i = 0, j = 0;
    char postfix[SIZE];
    char stack[SIZE];
    int top = -1;

    while (infix[i] != '\0')
    {
        // printf("%d ---->\n", i);
        if (infix[i] == ' ' || infix[i] == '\t')
            continue;

        if (isalnum(infix[i]))
        {
            postfix[j++] = infix[i];
            // printf("post %c\n", postfix[j]);
            // j++;
        }

        else if (infix[i] == '(')
        {
            stack[++top] = infix[i];
        }

        else if (infix[i] == ')')
        {
            while (top > -1 && stack[top] != '(')
                postfix[j++] = stack[top--];

            top--;
        }

        else if (isOperator(infix[i]))
        {
            while (top > -1 && precedence(stack[top]) >= precedence(infix[i]))
            {
                postfix[j++] = stack[top--];
                // printf("post-1 %c\n", postfix[j]);
                // j++;
            }
            stack[++top] = infix[i];
            // printf("stack-1 %c\n", stack[top]);
        }
        i++;
        // printf("stack %c\n", stack[top]);
    }

    // Pop
    while (top > -1)
    {
        if (stack[top] == '(')
        {
            printf("Invalid Expression\n"); goto back;
        }
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0';
    printf("Postfix: %s\n", postfix);
    back:
}

int main()
{
    // char infix[SIZE] = "a+b*(c^d-e)^(f+g*h)-i";
    char infix[SIZE] = "(a+b*c(";
    printf("Infix: %s\n", infix);
    infixToPostfix(infix);

    return 0;
}