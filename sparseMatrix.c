#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int row;
    int col;
    int value;
} sparse;

void readMatrix(int matrix[MAX][MAX], int *rows, int *cols);
int convertToSparse(int matrix[MAX][MAX], int rows, int cols, sparse a[]);
void displaySparse(sparse a[]);
void simpleTranspose(sparse a[], sparse b[]);
void fastTranspose(sparse a[], sparse b[]);

int main()
{
    int matrix[MAX][MAX];
    int rows, cols, choice;

    sparse a[MAX], b[MAX];

    readMatrix(matrix, &rows, &cols);

    convertToSparse(matrix, rows, cols, a);

    printf("\nSparse Matrix (3-Tuple Representation):\n");
    displaySparse(a);

    while (1)
    {
        printf("\n1. Simple Transpose");
        printf("\n2. Fast Transpose");
        printf("\n3. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                simpleTranspose(a, b);

                printf("\nTranspose using Simple Transpose:\n");
                displaySparse(b);
                break;

            case 2:
                fastTranspose(a, b);

                printf("\nTranspose using Fast Transpose:\n");
                displaySparse(b);
                break;

            case 3:
                printf("\nExiting program.\n");
                return 0;

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}

/* Function to read matrix */

void readMatrix(int matrix[MAX][MAX], int *rows, int *cols)
{
    int i, j;

    printf("Enter the number of rows: ");
    scanf("%d", rows);

    printf("Enter the number of columns: ");
    scanf("%d", cols);

    if (*rows <= 0 || *cols <= 0 ||
        *rows > MAX || *cols > MAX)
    {
        printf("Invalid matrix size\n");
        exit(1);
    }

    printf("Enter the elements of the matrix:\n");

    for (i = 0; i < *rows; i++)
    {
        for (j = 0; j < *cols; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

/* Function to convert matrix into sparse form */

int convertToSparse(int matrix[MAX][MAX],
                    int rows, int cols, sparse a[])
{
    int i, j;
    int k = 1;

    a[0].row = rows;
    a[0].col = cols;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (matrix[i][j] != 0)
            {
                if (k == MAX)
                {
                    printf("Too many non-zero elements\n");
                    exit(1);
                }

                a[k].row = i;
                a[k].col = j;
                a[k].value = matrix[i][j];

                k++;
            }
        }
    }

    a[0].value = k - 1;

    return k;
}

/* Function to display sparse matrix */

void displaySparse(sparse a[])
{
    int i;

    printf("Row\tColumn\tValue\n");

    for (i = 0; i <= a[0].value; i++)
    {
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
    }
}

/* Function for simple transpose */

void simpleTranspose(sparse a[], sparse b[])
{
    int i, j;
    int current = 1;

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;

    for (i = 0; i < a[0].col; i++)
    {
        for (j = 1; j <= a[0].value; j++)
        {
            if (a[j].col == i)
            {
                b[current].row = a[j].col;
                b[current].col = a[j].row;
                b[current].value = a[j].value;

                current++;
            }
        }
    }
}

/* Function for fast transpose */

void fastTranspose(sparse a[], sparse b[])
{
    int rowTerms[MAX];
    int startingPos[MAX];

    int i, j;
    int numCols = a[0].col;
    int numTerms = a[0].value;

    /* Handle empty sparse matrix */

    if (numTerms == 0)
    {
        b[0].row = a[0].col;
        b[0].col = a[0].row;
        b[0].value = 0;
        return;
    }

    /* Initialize rowTerms */

    for (i = 0; i < numCols; i++)
    {
        rowTerms[i] = 0;
    }

    /* Count elements in each column */

    for (i = 1; i <= numTerms; i++)
    {
        rowTerms[a[i].col]++;
    }

    /* Calculate starting positions */

    startingPos[0] = 1;

    for (i = 1; i < numCols; i++)
    {
        startingPos[i] = startingPos[i - 1]
                         + rowTerms[i - 1];
    }

    /* Header of transposed matrix */

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = numTerms;

    /* Place elements in transposed matrix */

    for (i = 1; i <= numTerms; i++)
    {
        j = startingPos[a[i].col];

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;

        startingPos[a[i].col]++;
    }
}
