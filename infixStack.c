#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 50
#define MAX_EXPRESSION_LENGTH 2000

static char operatorStack[MAX_STACK_SIZE];
static int topIndex = -1;

int isFull(void)
{
    return topIndex == MAX_STACK_SIZE - 1;
}

int isEmpty(void)
{
    return topIndex == -1;
}

void push(char symbol)
{
    if(isFull())
    {
        printf("Stack Overflow\n");
        exit(0);
    }

    operatorStack[++topIndex] = symbol;
}

char pop(void)
{
    if(isEmpty())
    {
        return '\0';
    }

    return operatorStack[topIndex--];
}

char peek(void)
{
    if(isEmpty())
    {
        return '\0';
    }

    return operatorStack[topIndex];
}

int precedence(char operatorSymbol)
{
    if(operatorSymbol == '^')
        return 3;

    if(operatorSymbol == '*' ||
       operatorSymbol == '/' ||
       operatorSymbol == '%')
        return 2;

    if(operatorSymbol == '+' ||
       operatorSymbol == '-')
        return 1;

    return 0;
}

int isRightAssociative(char operatorSymbol)
{
    return operatorSymbol == '^';
}

int isOperand(char character)
{
    return (character >= 'a' && character <= 'z') ||
           (character >= '0' && character <= '9');
}

int isOperator(char character)
{
    return character == '+' ||
           character == '-' ||
           character == '*' ||
           character == '/' ||
           character == '%' ||
           character == '^';
}

void infixToPostfix(const char *infixExpression,
                    char *postfixExpression)
{
    int i;
    int j = 0;
    char symbol;

    topIndex = -1;

    for(i = 0; infixExpression[i] != '\0'; i++)
    {
        symbol = infixExpression[i];

        if(symbol == ' ' || symbol == '\t')
            continue;

        if(isOperand(symbol))
        {
            postfixExpression[j++] = symbol;
        }

        else if(symbol == '(')
        {
            push(symbol);
        }

        else if(symbol == ')')
        {
            while(!isEmpty() && peek() != '(')
            {
                postfixExpression[j++] = pop();
            }

            if(!isEmpty() && peek() == '(')
            {
                pop();
            }
        }

        else if(isOperator(symbol))
        {
            while(!isEmpty() &&
                  peek() != '(' &&
                  (precedence(peek()) > precedence(symbol) ||
                   (precedence(peek()) == precedence(symbol) &&
                    !isRightAssociative(symbol))))
            {
                postfixExpression[j++] = pop();
            }

            push(symbol);
        }
    }

    while(!isEmpty())
    {
        postfixExpression[j++] = pop();
    }

    postfixExpression[j] = '\0';
}

int main(void)
{
    char infixExpression[MAX_EXPRESSION_LENGTH];
    char postfixExpression[MAX_EXPRESSION_LENGTH] = "";

    if(fgets(infixExpression,
             sizeof(infixExpression),
             stdin) == NULL)
    {
        return 0;
    }

    infixExpression[strcspn(infixExpression, "\n")] = '\0';

    infixToPostfix(infixExpression, postfixExpression);

    printf("%s\n", postfixExpression);

    return 0;
}