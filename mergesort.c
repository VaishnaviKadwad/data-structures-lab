
#include <stdio.h>
#define MAX 100

int b[MAX];

void merge(int a[], int lb, int mid, int ub)
{
    int i = lb;
    int j = mid + 1;
    int k = lb;

    while (i <= mid && j <= ub)
    {
        if (a[i] <= a[j])
        {
            b[k] = a[i];
            i++;
            k++;
        }
        else
        {
            b[k] = a[j];
            j++;
            k++;
        }
    }

    if (i > mid)
    {
        while (j <= ub)
        {
            b[k] = a[j];
            j++;
            k++;
        }
    }
    else
    {
        while (i <= mid)
        {
            b[k] = a[i];
            i++;
            k++;
        }
    }

    /* Copy contents of b to a */
    for (k = lb; k <= ub; k++)
    {
        a[k] = b[k];
    }
}

void mergeSort(int a[], int lb, int ub)
{
    int mid;

    if (lb < ub)
    {
        mid = (lb + ub) / 2;

        mergeSort(a, lb, mid);
        mergeSort(a, mid + 1, ub);

        merge(a, lb, mid, ub);
    }
}

int main()
{
    int a[MAX], n, i;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    mergeSort(a, 0, n - 1);

    printf("Sorted array:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}
