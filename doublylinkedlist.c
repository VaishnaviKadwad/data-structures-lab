
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *prev;
    struct node *next;
};

typedef struct node *NODE;

NODE head = NULL;

void insert()
{
    NODE newnode, temp;
    int item;

    newnode = (NODE)malloc(sizeof(struct node));

    if (newnode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Enter the item to be inserted: ");
    scanf("%d", &item);

    newnode->data = item;
    newnode->prev = NULL;
    newnode->next = NULL;

    /* Base condition: Empty list */
    if (head == NULL)
    {
        head = newnode;
        return;
    }

    /* Traverse to the last node */
    temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newnode;
    newnode->prev = temp;
}

void delete()
{
    NODE temp;

    /* Base condition 1: Empty list */
    if (head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    temp = head;

    /* Traverse to the last node */
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    /* Base condition 2: Only one node */
    if (head->next == NULL)
    {
        printf("Deleted item is %d\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    /* Delete the last node */
    printf("Deleted item is %d\n", temp->data);

    temp->prev->next = NULL;
    free(temp);
}

void display()
{
    NODE temp;

    if (head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    printf("List contents are:\n");

    temp = head;

    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n1. INSERT AT END\n");
        printf("2. DELETE FROM END\n");
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
