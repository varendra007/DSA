#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vertex
{
    int predecessor;
    int key;
    int colour; //white=1, grey=2, black=3
    int time_discovered;
    int time_finished;
    int num;
    int serialNo;
};

int **adjacency;
int vertices, edges;
FILE *graph, *ts;

int time = 0;

struct vertex *vert;

struct node
{
    int data;
    struct node *next;
};

struct node *head;

struct node *create_node()
{

    struct node *newnode = (struct node *)malloc(sizeof(struct node));

    if (newnode == NULL)
    {
        printf("\nCannot allocate memory for the new node\n");
        exit(0);
    }

    newnode->next = NULL;

    return newnode;
}

void insert_begin(int data)
{
    struct node *newnode, *temp;
    newnode = create_node();

    newnode->data = data;

    if (head == NULL)
    {
        head = newnode;
    }

    else
    {
        temp = head;
        head = newnode;
        newnode->next = temp;
    }
}

void DFS_VISIT(int h)
{
    time = time + 1;
    vert[h].time_discovered = time;
    vert[h].colour = 2;

    for (int i = 0; i < vertices; i++)
    {
        if (adjacency[h][i] == 1)
        {
            DFS_VISIT(i);
        }
    }

    vert[h].colour = 3;
    time = time + 1;
    vert[h].time_finished = time;
}

int main(int argc, char *argv[])
{

    graph = fopen("test/input2.graph", "r");
    fscanf(graph, "%d %d", &vertices, &edges);
    int x, y;

    ts = fopen("ts.txt", "w");

    adjacency = (int **)malloc(vertices * sizeof(int *));

    for (int i = 0; i < vertices; i++)
    {
        adjacency[i] = (int *)malloc(vertices * sizeof(int));
    }

    for (int j = 0; j < vertices; j++)
    {
        for (int k = 0; k < vertices; k++)
        {
            adjacency[j][k] = 0;
        }
    }

    for (int i = 0; i < edges; i++)
    {
        fscanf(graph, "%d %d", &x, &y);
        adjacency[x][y] = 1;
    }

    for (int k = 0; k < vertices; k++)
    {
        adjacency[k][k] = 0;
    }

    vert = (struct vertex *)malloc(vertices * sizeof(struct vertex));

    for (int i = 0; i < vertices; i++)
    {
        vert[i].colour = 1;
        vert[i].predecessor = -1;
        vert[i].serialNo = -1;
        vert[i].time_finished = -1;
    }

    time = 0;

    for (int i = 0; i < vertices; i++)
    {

        if (vert[i].colour == 1)
        {

            DFS_VISIT(i);
        }
    }
    int SrNo = 0;
    for (int i = 0; i < vertices; i++)
    {
        int min = INT_MAX;
        int idx = -1;
        for (int j = 0; j < vertices; j++)
        {
            if (vert[j].time_finished < min && vert[j].serialNo == -1)
            {
                min = vert[j].time_finished;
                idx = j;
            }
        }
        vert[idx].serialNo = SrNo;
        SrNo++;
        insert_begin(idx);
    }

    struct node *traversal;
    traversal = head;

    while (traversal != NULL)
    {

        fprintf(ts, "%d\n", traversal->data);

        traversal = traversal->next;
    }
}