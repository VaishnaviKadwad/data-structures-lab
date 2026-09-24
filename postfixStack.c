/*
 * Evaluation of a postfix expression.
 *
 * Read one postfix expression from standard input and print its value.
 * The lab sheet in the Brief pane is the whole contract: what a token is,
 * what each of the six operators means, and what your program must print.
 *
 * HOW YOU SOLVE IT IS YOURS. A stack you write yourself, a plain array you
 * index by hand, a linked list, recursion -- nothing here reads your source.
 * Every test runs your program and reads the answer out of whatever it
 * printed. Only the answer has to be right.
 */

#include <stdio.h>
#include<ctype.h>
#define MAX 100
int stack[MAX];
int top=-1;
void push(int x)
{
    stack[++top]=x;

}
int pop(){
    return stack[top--];
}
int main(void)
{
    char postfix[MAX];
    int i,a,b, result;
    int j;

    fgets(postfix,MAX,stdin);
    i=0;

    while(postfix[i]!='\0')
    {
        if (postfix[i]==' '|| postfix[i]=='\n')
        {
            i++;
        }
        else if(isdigit((unsigned char)postfix[i]) ||
                (postfix[i]=='-' && isdigit((unsigned char)postfix[i+1])))
        {
            int num=0;
            int sign=1;

            if(postfix[i]=='-')
            {
                sign=-1;
                i++;
            }

            while(isdigit((unsigned char)postfix[i]))
            {
                num=num*10+(postfix[i]-'0');
                i++;
            }

            push(sign*num);
        }
        else
        {
            b=pop();
            a=pop();

            switch(postfix[i]){
                case '+':
                    result=a+b;
                    break;

                case '-':
                    result=a-b;
                    break;

                case '*':
                    result=a*b;
                    break;

                case '/':
                    result=a/b;
                    break;

                case '%':
                    result=a%b;
                    break;

                case '^':
                    result=1;
                    for(j=0;j<b;j++)
                    {
                        result=result*a;
                    }
                    break;
            }

            push(result);
            i++;
        }
    }

    printf("%d",pop());

    /* TODO: read the expression from standard input. It is one line of
       tokens separated by spaces, and the line is the whole expression. */

    /* TODO: tell an operand from an operator. An operator is a token of
       exactly one character, one of + - * / % ^. A token like -5 is an
       operand: a negative number, not a minus sign. */

    /* TODO: evaluate it. In "a b op" the left operand is the one that
       appeared first, so 9 4 - is 9 - 4 and not 4 - 9. */

    /* TODO: print the value. It has to be the last number you print. */

    return 0;
}
