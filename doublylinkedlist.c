
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
    int key;
    NODE temp;
    printf("Enter the key to be deleted: ");
    scanf("%d", &key);

    /* Base condition 1: Empty list */
    if (head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    temp = head;

    while(temp!=NULL && temp->data != key)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Key not found\n");
        return;
    }
    if(temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    if(temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    printf("Deleted item is %d\n", temp->data);
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
        printf("\n1. INSERT \n");
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
