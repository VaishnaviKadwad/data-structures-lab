#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100

typedef struct
{
    float coef;
    int expon;
} polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;

void add(int startA, int finishA, int startB, int finishB,
         int *startD, int *finishD);

void attach(float coefficient, int exponent);

int compare(int x, int y)
{
    if (x < y)
        return -1;
    else if (x == y)
        return 0;
    else
        return 1;
}

void add(int startA, int finishA, int startB, int finishB,
         int *startD, int *finishD)
{
    /* add A(x) and B(x) to obtain D(x) */

    float coefficient;

    *startD = avail;

    while (startA <= finishA && startB <= finishB)
    {
        switch (compare(terms[startA].expon,
                        terms[startB].expon))
        {
            case -1:
                /* a expon < b expon */

                attach(terms[startB].coef,
                       terms[startB].expon);

                startB++;
                break;

            case 0:
                /* equal exponents */

                coefficient = terms[startA].coef +
                              terms[startB].coef;

                if (coefficient)
                    attach(coefficient,
                           terms[startA].expon);

                startA++;
                startB++;
                break;

            case 1:
                /* a expon > b expon */

                attach(terms[startA].coef,
                       terms[startA].expon);

                startA++;
                break;
        }
    }

    /* add remaining terms of A(x) */

    for (; startA <= finishA; startA++)
        attach(terms[startA].coef,
               terms[startA].expon);

    /* add remaining terms of B(x) */

    for (; startB <= finishB; startB++)
        attach(terms[startB].coef,
               terms[startB].expon);

    *finishD = avail - 1;
}

void attach(float coefficient, int exponent)
{
    /* add a new term to the polynomial */

    if (avail >= MAX_TERMS)
    {
        fprintf(stderr, "Too many terms in the polynomial\n");
        exit(0);
    }

    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

int main()
{
    int startA, finishA;
    int startB, finishB;
    int startD, finishD;
    int i;
    int n;

    /* Enter polynomial A(x) */

    printf("Enter the number of terms in A(x): ");
    scanf("%d", &n);

    startA = avail;

    printf("Enter coefficient and exponent of each term of A(x):\n");

    for (i = 0; i < n; i++)
    {
        float coefficient;
        int exponent;

        scanf("%f %d", &coefficient, &exponent);

        attach(coefficient, exponent);
    }

    finishA = avail - 1;

    /* Enter polynomial B(x) */

    printf("Enter the number of terms in B(x): ");
    scanf("%d", &n);

    startB = avail;

    printf("Enter coefficient and exponent of each term of B(x):\n");

    for (i = 0; i < n; i++)
    {
        float coefficient;
        int exponent;

        scanf("%f %d", &coefficient, &exponent);

        attach(coefficient, exponent);
    }

    finishB = avail - 1;

    add(startA, finishA, startB, finishB,
        &startD, &finishD);

    /* display the result */

    printf("\nA(x) + B(x) = ");

    for (i = startD; i <= finishD; i++)
    {
        if (i > startD && terms[i].coef >= 0)
            printf("+ ");

        printf("%.0fx^%d ",
               terms[i].coef,
               terms[i].expon);
    }

    printf("\n");

    return 0;
}