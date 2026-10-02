#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *queue;
int capacity;
int front = 0;
int rear = -1;
int count = 0;

void enqueue(int value)
{
    if (count == capacity)
    {
        printf("OVERFLOW\n");
        return;
    }

    rear = (rear + 1) % capacity;
    queue[rear] = value;
    count++;

    printf("ENQUEUED %d\n", value);
}

void dequeue()
{
    if (count == 0)
    {
        printf("UNDERFLOW\n");
        return;
    }

    printf("DEQUEUED %d\n", queue[front]);

    front = (front + 1) % capacity;
    count--;

    if (count == 0)
    {
        front = 0;
        rear = -1;
    }
}

void display()
{
    if (count == 0)
    {
        printf("QUEUE EMPTY\n");
        return;
    }

    printf("QUEUE");

    for (int i = 0; i < count; i++)
    {
        int index = (front + i) % capacity;
        printf(" %d", queue[index]);
    }

    printf("\n");
}

int main()
{
    int Q;
    char operation[20];
    int value;

    scanf("%d", &capacity);

    queue = (int *)malloc(capacity * sizeof(int));

    if (queue == NULL)
    {
        return 1;
    }

    scanf("%d", &Q);

    for (int i = 0; i < Q; i++)
    {
        scanf("%s", operation);

        if (strcmp(operation, "ENQUEUE") == 0)
        {
            scanf("%d", &value);
            enqueue(value);
        }
        else if (strcmp(operation, "DEQUEUE") == 0)
        {
            dequeue();
        }
        else if (strcmp(operation, "DISPLAY") == 0)
        {
            display();
        }
    }

    free(queue);

    return 0;
}