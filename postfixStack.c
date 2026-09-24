#include <stdio.h>
#include <ctype.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int x)
{
    stack[++top] = x;
}

int pop()
{
    return stack[top--];
}

int main()
{
    char postfix[MAX];
    int i, a, b, result;

    printf("Enter postfix expression: ");
    fgets(postfix, MAX, stdin);

    i = 0;

    while (postfix[i] != '\0')
    {
        if (postfix[i] == ' ' || postfix[i] == '\n')
        {
            i++;
        }
        else if (isdigit(postfix[i]))
        {
            int num = 0;

            while (isdigit(postfix[i]))
            {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }

            push(num);
        }
        else
        {
            b = pop();
            a = pop();

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
                    result = a / b;
                    break;

                case '%':
                    result = a % b;
                    break;

                default:
                    printf("Invalid operator: %c\n", postfix[i]);
                    return 1;
            }

            push(result);
            i++;
        }
    }

    printf("Result = %d\n", pop());

    return 0;
}