#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

int stack[MAX];
int top = -1;
int error = 0;

void push(int x)
{
    if (top == MAX - 1)
    {
        printf("Stack Overflow\n");
        error = 1;
        return;
    }

    stack[++top] = x;
}

int pop()
{
    if (top == -1)
    {
        printf("Stack Underflow\n");
        error = 1;
        return 0;
    }

    return stack[top--];
}

int main()
{
    char postfix[MAX];
    int i, a, b, result;
    int num;

    printf("Enter postfix expression: ");
    fgets(postfix, MAX, stdin);

    i = 0;

    while (postfix[i] != '\0' && postfix[i] != '\n')
    {
        if (postfix[i] == ' ' || postfix[i] == '\t')
        {
            i++;
        }
        else if (isdigit((unsigned char)postfix[i]))
        {
            num = 0;

            while (isdigit((unsigned char)postfix[i]))
            {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }

            push(num);

            if (error)
                return 1;
        }
        else
        {
            b = pop();
            a = pop();

            if (error)
                return 1;

            switch (postfix[i])
            {
                case '+':
                    result = a + b;
                    break;

                case '-':
                    result = a - b;
                    break;

                case '*':
                    result = a * b;
                    break;

                case '/':
                    if (b == 0)
                    {
                        printf("Division by zero\n");
                        return 1;
                    }

                    result = a / b;
                    break;

                case '%':
                    if (b == 0)
                    {
                        printf("Division by zero\n");
                        return 1;
                    }

                    result = a % b;
                    break;

                default:
                    printf("Invalid operator: %c\n", postfix[i]);
                    return 1;
            }

            push(result);

            if (error)
                return 1;

            i++;
        }
    }

    if (top != 0)
    {
        printf("Invalid postfix expression\n");
        return 1;
    }

    printf("Result = %d\n", pop());

    return 0;
}
