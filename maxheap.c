#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int heap[MAX];
int n = 0;

void insert()
{
    int item, i;

    if (n == MAX - 1)
    {
        printf("Heap is Full\n");
        return;
    }

    printf("Enter the item: ");
    scanf("%d", &item);

    i = ++n;

    while ((i != 1) && (item > heap[i / 2]))
    {
        heap[i] = heap[i / 2];
        i = i / 2;
    }

    heap[i] = item;
}

void delete()
{
    int item, temp, parent, child;

    if (n == 0)
    {
        printf("Heap is Empty\n");
        return;
    }

    item = heap[1];

    temp = heap[n];
    n--;

    parent = 1;
    child = 2;

    while (child <= n)
    {
        if ((child < n) && (heap[child] < heap[child + 1]))
        {
            child++;
        }

        if (temp >= heap[child])
        {
            break;
        }

        heap[parent] = heap[child];

        parent = child;
        child = child * 2;
    }

    heap[parent] = temp;

    printf("Deleted item is %d\n", item);
}

void display()
{
    int i;

    if (n == 0)
    {
        printf("Heap is Empty\n");
        return;
    }

    printf("Heap contents are:\n");

    for (i = 1; i <= n; i++)
    {
        printf("%d ", heap[i]);
    }

    printf("\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n1. INSERT");
        printf("\n2. DELETE");
        printf("\n3. DISPLAY");
        printf("\n4. EXIT");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                insert();
                break;

            case 2:
                delete();
                break;

            case 3:
                display();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
/*
using 0 indexing

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int heap[MAX];
int n = 0;

void insert()
{
    int item, i;

    if (n == MAX - 1)
    {
        printf("Heap is Full\n");
        return;
    }

    printf("Enter the item: ");
    scanf("%d", &item);

    i = ++n;

    while ((i != 1) && (item > heap[i / 2]))
    {
        heap[i] = heap[i / 2];
        i = i / 2;
    }

    heap[i] = item;
}

void delete()
{
    int item, temp, parent, child;

    if (n == 0)
    {
        printf("Heap is Empty\n");
        return;
    }

    item = heap[1];

    temp = heap[n];
    n--;

    parent = 1;
    child = 2;

    while (child <= n)
    {
        if ((child < n) && (heap[child] < heap[child + 1]))
        {
            child++;
        }

        if (temp >= heap[child])
        {
            break;
        }

        heap[parent] = heap[child];

        parent = child;
        child = child * 2;
    }

    heap[parent] = temp;

    printf("Deleted item is %d\n", item);
}

void display()
{
    int i;

    if (n == 0)
    {
        printf("Heap is Empty\n");
        return;
    }

    printf("Heap contents are:\n");

    for (i = 1; i <= n; i++)
    {
        printf("%d ", heap[i]);
    }

    printf("\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n1. INSERT");
        printf("\n2. DELETE");
        printf("\n3. DISPLAY");
        printf("\n4. EXIT");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                insert();
                break;

            case 2:
                delete();
                break;

            case 3:
                display();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}*/