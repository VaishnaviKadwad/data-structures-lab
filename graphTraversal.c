#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int adj[MAX][MAX];
int visited[MAX];
int n;

void createGraph()
{
    int i, j;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &adj[i][j]);
        }
    }
}

void DFS(int v)
{
    int i;

    visited[v] = 1;
    printf("%d\n", v);

    for (i = 0; i < n; i++)
    {
        if (adj[v][i] == 1 && visited[i] == 0)
        {
            DFS(i);
        }
    }
}

void BFS(int start)
{
    int queue[MAX];
    int front = 0, rear = -1;
    int v, i;

    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    visited[start] = 1;
    queue[++rear] = start;

    while (front <= rear)
    {
        v = queue[front++];

        printf("%d\n", v);

        for (i = 0; i < n; i++)
        {
            if (adj[v][i] == 1 && visited[i] == 0)
            {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
}

int main()
{
    int choice, start, i;

    createGraph();

    while (1)
    {
        printf("\n1. DEPTH FIRST SEARCH");
        printf("\n2. BREADTH FIRST SEARCH");
        printf("\n3. EXIT");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter the starting vertex: ");
                scanf("%d", &start);

                if (start < 0 || start >= n)
                {
                    printf("Invalid vertex\n");
                    break;
                }

                for (i = 0; i < n; i++)
                {
                    visited[i] = 0;
                }

                printf("DFS Traversal:\n");
                DFS(start);
                break;

            case 2:
                printf("Enter the starting vertex: ");
                scanf("%d", &start);

                if (start < 0 || start >= n)
                {
                    printf("Invalid vertex\n");
                    break;
                }

                printf("BFS Traversal:\n");
                BFS(start);
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}