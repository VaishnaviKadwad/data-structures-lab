
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

typedef struct node *NODE;

NODE root = NULL;

NODE insert(NODE root, int item)
{
    NODE newnode;

    if (root == NULL)
    {
        newnode = (NODE)malloc(sizeof(struct node));

        if (newnode == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }

        newnode->data = item;
        newnode->left = NULL;
        newnode->right = NULL;

        return newnode;
    }

    if (item < root->data)
    {
        root->left = insert(root->left, item);
    }
    else if (item > root->data)
    {
        root->right = insert(root->right, item);
    }
    else
    {
        printf("Duplicate elements are not allowed\n");
    }

    return root;
}

void inorder(NODE root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(NODE root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(NODE root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main()
{
    int n,choice, item;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &item);
        root = insert(root, item);
    }

    while (1)
    {
        
        printf("\n1. INORDER TRAVERSAL");
        printf("\n2. PREORDER TRAVERSAL");
        printf("\n3. POSTORDER TRAVERSAL");
        printf("\n4. EXIT");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            
            case 1:
                if (root == NULL)
                    printf("Tree is Empty\n");
                else
                {
                    printf("Inorder traversal: ");
                    inorder(root);
                    printf("\n");
                }
                break;

            case 2:
                if (root == NULL)
                    printf("Tree is Empty\n");
                else
                {
                    printf("Preorder traversal: ");
                    preorder(root);
                    printf("\n");
                }
                break;

            case 3:
                if (root == NULL)
                    printf("Tree is Empty\n");
                else
                {
                    printf("Postorder traversal: ");
                    postorder(root);
                    printf("\n");
                }
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
