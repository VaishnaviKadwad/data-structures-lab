
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

typedef struct node *NODE;

NODE top = NULL;

void push()
{
    NODE temp;
    int item;

    temp = (NODE)malloc(sizeof(struct node));

    if (temp == NULL)
    {
        printf("memory allocation failed\n");
        return;
    }

    printf("Enter the item to be pushed: ");
    scanf("%d", &item);

    temp->data = item;
    temp->next = top;
    top = temp;
}

void pop()
{
    NODE temp;

    if (top == NULL)
    {
        printf("Stack Underflow\n");
        return;
    }

    temp = top;
    printf("Deleted item is %d\n", temp->data);

    top = top->next;
    free(temp);
}

void display()
{
    NODE temp;

    if (top == NULL)
    {
        printf("Stack is Empty\n");
        return;
    }

    printf("Stack contents are:\n");
    temp = top;

    while (temp != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n1. PUSH\n");
        printf("2. POP\n");
        printf("3. DISPLAY\n");
        printf("4. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                push();
                break;

            case 2:
                pop();
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
