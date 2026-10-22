
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int info;
    struct node *link;
};

typedef struct node *NODE;

NODE front = NULL;
NODE rear = NULL;

void insert()
{
    NODE temp;
    int item;

    temp = (NODE)malloc(sizeof(struct node));

    if (temp == NULL)
    {
        printf("Queue Overflow\n");
        return;
    }

    printf("Enter the item to be inserted: ");
    scanf("%d", &item);

    temp->info = item;
    temp->link = NULL;

    if (front == NULL)
    {
        front = temp;
        rear = temp;
    }
    else
    {
        rear->link = temp;
        rear = temp;
    }
}

void delete()
{
    NODE temp;

    if (front == NULL)
    {
        printf("Queue Underflow\n");
        return;
    }

    temp = front;
    printf("Deleted item is %d\n", temp->info);

    front = front->link;

    if (front == NULL)
    {
        rear = NULL;
    }

    free(temp);
}

void display()
{
    NODE temp;

    if (front == NULL)
    {
        printf("Queue is Empty\n");
        return;
    }

    printf("Queue contents are:\n");
    temp = front;

    while (temp != NULL)
    {
        printf("%d ", temp->info);
        temp = temp->link;
    }

    printf("\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n1. INSERT\n");
        printf("2. DELETE\n");
        printf("3. DISPLAY\n");
        printf("4. EXIT\n");
        printf("Enter your choice: ");
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
