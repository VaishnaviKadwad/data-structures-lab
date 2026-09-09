#include <stdio.h>

#define MAX 100

/* Structure to store a sparse matrix in 3-tuple form */
typedef struct
{
    int row;
    int col;
    int value;
} sparse;

/* Function declarations */
void readMatrix(int matrix[MAX][MAX], int *rows, int *cols);
int convertToSparse(int matrix[MAX][MAX], int rows, int cols, sparse a[]);
void displaySparse(sparse a[]);
void simpleTranspose(sparse a[], sparse b[]);
void fastTranspose(sparse a[], sparse b[]);


int main()
{
    int matrix[MAX][MAX];
    int rows, cols;
    sparse a[MAX];
    sparse b[MAX];
    int choice;

    /* Read the normal matrix from the user */
    readMatrix(matrix, &rows, &cols);

    /* Convert the normal matrix into sparse matrix */
    convertToSparse(matrix, rows, cols, a);

    printf("\nSparse Matrix (3-Tuple Representation):\n");
    displaySparse(a);

    /* Menu for selecting transpose method */
    printf("\nChoose the method for transpose:\n");
    printf("1. Simple Transpose\n");
    printf("2. Fast Transpose\n");
    printf("3. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            /* Perform Simple Transpose */
            simpleTranspose(a, b);

            printf("\nTranspose using Simple Transpose Method:\n");
            displaySparse(b);
            break;

        case 2:
            /* Perform Fast Transpose */
            fastTranspose(a, b);

            printf("\nTranspose using Fast Transpose Method:\n");
            displaySparse(b);
            break;

        case 3:
            printf("\nExiting program...\n");
            break;

        default:
            printf("\nInvalid choice!\n");
    }

    return 0;
}


/* Function to read the matrix from the user */
void readMatrix(int matrix[MAX][MAX], int *rows, int *cols)
{
    int i, j;

    printf("Enter the number of rows: ");
    scanf("%d", rows);

    printf("Enter the number of columns: ");
    scanf("%d", cols);

    printf("Enter the elements of the matrix:\n");

    for (i = 0; i < *rows; i++)
    {
        for (j = 0; j < *cols; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}


/*
   Function to convert normal matrix into
   sparse matrix using 3-tuple representation.

   First row stores:
   row   -> number of rows
   col   -> number of columns
   value -> number of non-zero elements
*/
int convertToSparse(int matrix[MAX][MAX], int rows, int cols, sparse a[])
{
    int i, j;
    int k = 1;

    a[0].row = rows;
    a[0].col = cols;

    /* Store only non-zero elements */
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (matrix[i][j] != 0)
            {
                a[k].row = i;
                a[k].col = j;
                a[k].value = matrix[i][j];

                k++;
            }
        }
    }

    /* Store number of non-zero elements */
    a[0].value = k - 1;

    return k;
}


/* Function to display a sparse matrix */
void displaySparse(sparse a[])
{
    int i;

    printf("Row\tColumn\tValue\n");

    for (i = 0; i <= a[0].value; i++)
    {
        printf("%d\t%d\t%d\n",
               a[i].row,
               a[i].col,
               a[i].value);
    }
}


/*
   Simple Transpose Method

   For every column of the original sparse matrix,
   find all elements belonging to that column and
   interchange row and column.
*/
void simpleTranspose(sparse a[], sparse b[])
{
    int i, j;
    int current = 1;

    /* Interchange rows and columns */
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;

    /*
       Visit each column of the original matrix
       in order.
    */
    for (i = 0; i < a[0].col; i++)
    {
        /*
           Search all non-zero elements for
           the current column.
        */
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


/*
   Fast Transpose Method

   rowTerms[i] -> number of elements in column i
                  of the original matrix.

   startingPos[i] -> starting position of column i
                     in the transposed matrix.
*/
void fastTranspose(sparse a[], sparse b[])
{
    int rowTerms[MAX];
    int startingPos[MAX];

    int i, j;
    int numCols = a[0].col;
    int numTerms = a[0].value;

    /* If there are no non-zero elements */
    if (numTerms == 0)
    {
        b[0].row = numCols;
        b[0].col = a[0].row;
        b[0].value = 0;
        return;
    }

    /* Initialize rowTerms */
    for (i = 0; i < numCols; i++)
    {
        rowTerms[i] = 0;
    }

    /*
       Count the number of elements in each
       column of the original matrix.
    */
    for (i = 1; i <= numTerms; i++)
    {
        rowTerms[a[i].col]++;
    }

    /*
       Store the starting position of each column
       in the transposed matrix.
    */
    startingPos[0] = 1;

    for (i = 1; i < numCols; i++)
    {
        startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
    }

    /* Header of transposed matrix */
    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;

    /*
       Place each element directly into its
       correct position in the transposed matrix.
    */
    for (i = 1; i <= numTerms; i++)
    {
        j = startingPos[a[i].col];

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;

        startingPos[a[i].col]++;
    }
}