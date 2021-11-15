#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #define __INT_MAX__ 9999

int len = 0;

struct node
{
    int data;
    struct node *next;
};

struct node *head = NULL;

struct vertex
{
    int colour;      // white=1, grey=2, black=3
    int predecessor; // previous node in BFS
    int distance;    // distance from source vertex
};

struct node *create_node();

//void Enqueue(int data, struct node *head);
//int Dequeue(struct node *head);
//int IsQueueEmpty(struct node *head);

struct node *create_node()
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));

    if (newnode == NULL)
    {
        printf("\nError in allocating space for newnode\n");
        exit(0);
    }

    newnode->next = NULL;

    return newnode;
}

void Enqueue(int data)
{

    struct node *newnode = create_node();
    newnode->data = data;

    if (head == NULL)
    {
        head = newnode;
    }

    else
    {
        newnode->next = head;
        head = newnode;
    }

    len++;
}

int Dequeue()
{
    struct node *traversal;
    int data;

    if (head == NULL)
    {
        printf("Error: Dequeue not possible since the list is already empty.");
        exit(0);
    }

    else if (head->next == NULL)
    {
        data = head->data;
        head = NULL;
        len--;
        return data;
    }

    else
    {
        traversal = head;

        while (traversal->next->next != NULL)
        {
            traversal = traversal->next;
        }

        data = traversal->next->data;
        traversal->next = NULL;
        len--;

        return data;
    }
}

int IsQueueEmpty()
{
    if (head == NULL)
    {
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int edges, vertices;
    struct node *headyy = NULL;
    int x, y;

    FILE *graph, *sd;

    graph = fopen("Assignment#6-io/input1.graph", "r");

    fscanf(graph, "%d %d", &vertices, &edges);

    int **adjacency = (int **)malloc(vertices * sizeof(int *));

    for (int i = 0; i < vertices; i++)
    {
        adjacency[i] = (int *)malloc(vertices * sizeof(int));
    }

    int *distances = (int *)malloc(vertices * sizeof(int));

    int *count = (int *)malloc(vertices * sizeof(int *)); // array to check if a node is present in the graph or not

    struct vertex *vert = (struct vertex *)malloc(vertices * sizeof(struct vertex));

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            adjacency[i][j] = 0;
        }
    }

    while (fscanf(graph, "%d %d", &x, &y) != EOF)
    {
        adjacency[x][y] = 1;
        adjacency[y][x] = 1;

        count[x]++;
        count[y]++;
    }

    //BFS Algorithm

    for (int i = 1; i < vertices; i++)
    {
        vert[i].colour = 1;
        vert[i].distance = -1;
        vert[i].predecessor = -1;
    }

    vert[0].colour = 2;
    vert[0].distance = 0;
    vert[0].predecessor = INT_MAX;

    int current_node = 0;

    Enqueue(0);

    while (len)
    {
        current_node = Dequeue();

        for (int i = 0; i < vertices; i++)
        {
            if (adjacency[current_node][i])
            {
                if (vert[i].colour == 1)
                {
                    vert[i].colour = 2;
                    vert[i].distance = vert[current_node].distance + 1;
                    vert[i].predecessor = current_node;

                    Enqueue(i);
                }
            }
        }

        vert[current_node].colour = 3;
    }

    sd = fopen("Assignment#6-io/sd.txt", "w");

    for (int i = 0; i < vertices; i++)
    {
        fprintf(sd, "%d\n", vert[i].distance);
    }

    fclose(graph);
    fclose(sd);

    return 0;
}