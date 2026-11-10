#include <stdio.h>
#include <stdlib.h>

int *queue = NULL;
int front = -1;
int rear = -1;
int size = 0;
int capacity = 0;

void resizeQueue()
{
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;

    int *newQueue = (int *)malloc(newCapacity * sizeof(int));

    if (newQueue == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
    {
        newQueue[i] = queue[(front + i) % capacity];
    }

    free(queue);

    queue = newQueue;
    capacity = newCapacity;

    if (size == 0)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = 0;
        rear = size - 1;
    }
}

void enqueue(int value)
{
    if (size == capacity)
    {
        resizeQueue();
    }

    if (front == -1 && rear == -1)
    {
        front = rear = 0;
    }
    else
    {
        rear = (rear + 1) % capacity;
    }

    queue[rear] = value;
    size++;

    printf("%d inserted into queue\n", value);
}

void dequeue()
{
    if (size == 0)
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Deleted element: %d\n", queue[front]);

    if (size == 1)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % capacity;
    }

    size--;
}

void display()
{
    if (size == 0)
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue elements are:\n");

    for (int i = 0; i < size; i++)
    {
        printf("%d ", queue[(front + i) % capacity]);
    }

    printf("\n");
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n1. Enqueue");
        printf("\n2. Dequeue");
        printf("\n3. Display");
        printf("\n4. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter the element: ");
                scanf("%d", &value);

                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                free(queue);
                queue = NULL;

                printf("Exiting\n");
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
