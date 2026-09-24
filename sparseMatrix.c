#include <stdio.h>
#include <string.h>

#define MAX_TERMS 60005
#define MAX_COLUMNS 200005

typedef struct
{
    int row;
    int col;
    int value;
} sparse;

/* Function declarations */
void readMatrix(sparse a[], int *rows, int *cols);
void displaySparse(sparse a[]);
void simpleTranspose(sparse a[], sparse b[]);
void fastTranspose(sparse a[], sparse b[]);


int main()
{
    static sparse a[MAX_TERMS];
    static sparse b[MAX_TERMS];

    char command[25];
    int rows, cols;

    /* Read command */
    scanf("%24s", command);

    /* Read rows and columns */
    scanf("%d %d", &rows, &cols);

    /* Read matrix and convert directly to sparse form */
    readMatrix(a, &rows, &cols);

    if (strcmp(command, "SPARSE") == 0)
    {
        displaySparse(a);
    }
    else if (strcmp(command, "SIMPLE") == 0)
    {
        simpleTranspose(a, b);
        displaySparse(b);
    }
    else if (strcmp(command, "FAST") == 0)
    {
        fastTranspose(a, b);
        displaySparse(b);
    }

    return 0;
}


/*
    Read the matrix and directly store
    non-zero elements in sparse form.

    a[0]:
    row   = number of rows
    col   = number of columns
    value = number of non-zero elements
*/
void readMatrix(sparse a[], int *rows, int *cols)
{
    int i, j;
    int value;
    int k = 1;

    a[0].row = *rows;
    a[0].col = *cols;
    a[0].value = 0;

    for (i = 0; i < *rows; i++)
    {
        for (j = 0; j < *cols; j++)
        {
            scanf("%d", &value);

            if (value != 0)
            {
                a[k].row = i;
                a[k].col = j;
                a[k].value = value;

                k++;
                a[0].value++;
            }
        }
    }
}


/* Display sparse matrix in 3-tuple form */
void displaySparse(sparse a[])
{
    int i;

    for (i = 0; i <= a[0].value; i++)
    {
        printf("%d %d %d\n",
               a[i].row,
               a[i].col,
               a[i].value);
    }
}


/*
    Simple Transpose

    Time Complexity:
    O(columns * non-zero terms)
*/
void simpleTranspose(sparse a[], sparse b[])
{
    int i, j;
    int k = 1;

    /* Header of transposed matrix */
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;

    /*
        Process each column of the
        original matrix.
    */
    for (i = 0; i < a[0].col; i++)
    {
        /*
            Search all non-zero elements
            for the current column.
        */
        for (j = 1; j <= a[0].value; j++)
        {
            if (a[j].col == i)
            {
                b[k].row = a[j].col;
                b[k].col = a[j].row;
                b[k].value = a[j].value;

                k++;
            }
        }
    }
}


/*
    Fast Transpose

    rowTerms[i] stores the number of
    non-zero elements in column i.

    startingPos[i] stores the starting
    position of column i in the result.

    Time Complexity:
    O(columns + non-zero terms)
*/
void fastTranspose(sparse a[], sparse b[])
{
    static int rowTerms[MAX_COLUMNS];
    static int startingPos[MAX_COLUMNS];

    int i, j;
    int numCols = a[0].col;
    int numTerms = a[0].value;

    /* Header of transposed matrix */
    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;

    /* No non-zero elements */
    if (numTerms == 0)
    {
        return;
    }

    /*
        Initialize rowTerms.
    */
    for (i = 0; i < numCols; i++)
    {
        rowTerms[i] = 0;
    }

    /*
        Count non-zero elements
        in each column.
    */
    for (i = 1; i <= numTerms; i++)
    {
        rowTerms[a[i].col]++;
    }

    /*
        Calculate starting position
        of each column.
    */
    startingPos[0] = 1;

    for (i = 1; i < numCols; i++)
    {
        startingPos[i] =
            startingPos[i - 1] + rowTerms[i - 1];
    }

    /*
        Place each element directly
        in its correct position.
    */
    for (i = 1; i <= numTerms; i++)
    {
        j = a[i].col;

        b[startingPos[j]].row = a[i].col;
        b[startingPos[j]].col = a[i].row;
        b[startingPos[j]].value = a[i].value;

        startingPos[j]++;
    }
}
