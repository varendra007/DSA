#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int vertex;
    struct node *next;
    int parent;
} node;

node *topo_sort = NULL;

node *createnode(int vertex) //creating a node
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->vertex = vertex;
    newnode->next = NULL;
    newnode->parent = -2;
    return newnode;
}

typedef struct Graph // format of struct graph
{
    struct node **lsvertices;
    struct node **adjlists;
} Graph;

Graph *creategraph(int vertices) // creates the memory for the entire graph and does initialization work and all
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->adjlists = (node **)malloc(vertices * sizeof(node *));
    graph->lsvertices = (node **)malloc(vertices * sizeof(node *));
    // graph->num_vertices = vertices;
    for (int i = 0; i < vertices; i++)
    {
        graph->adjlists[i] = NULL;
        graph->lsvertices[i] = createnode(i);
    }
    return graph;
}

void addedge(Graph *graph, int src, int dest) // reads edges and then adds them in their respective adjency lists
{
    node *newnode = createnode(dest); // Inserting dest at the beginning of src
    newnode->next = graph->adjlists[src];
    graph->adjlists[src] = newnode;
}

void insertbegin(int vertex) // insert at the beginning of the list topo_sort
{
    node *tail = createnode(vertex);
    tail->next = topo_sort;
    topo_sort = tail;
    // free(tail);
}

void dfs_visit(Graph *graph, int i) // visit adjacency list of every vertex and if it's unvisited check it's adjacency list recursively
{
    node *temp = graph->adjlists[i];
    if (temp == NULL)
    {
        return;
    }
    else
    {
        if (temp->next == NULL)
        {
            if (temp->parent == -2 && graph->lsvertices[temp->vertex]->parent == -2)
            {
                temp->parent = graph->lsvertices[i]->vertex;
                graph->lsvertices[temp->vertex]->parent = -1;
                dfs_visit(graph, temp->vertex);
                insertbegin(temp->vertex);
            }
            else
            {
                return;
            }
        }
        else
        {
            while (temp->next)
            {
                if (temp->parent == -2 && graph->lsvertices[temp->vertex]->parent == -2)
                {
                    temp->parent = graph->lsvertices[i]->vertex;
                    graph->lsvertices[temp->vertex]->parent = -1;
                    dfs_visit(graph, temp->vertex);
                    insertbegin(temp->vertex);
                    temp = temp->next;
                }
                else
                {
                    temp = temp->next;
                }
            }
            if (temp->parent == -2 && graph->lsvertices[temp->vertex]->parent == -2)
            {
                temp->parent = graph->lsvertices[i]->vertex;
                graph->lsvertices[temp->vertex]->parent = -1;
                dfs_visit(graph, temp->vertex);
                insertbegin(temp->vertex);
                return;
            }
            else
            {
                return;
            }
        }
    }
}

void dfs(Graph *graph, int vertices) // checks dfs for every vertex
{
    for (int i = 0; i < vertices; i++)
    {
        if (graph->lsvertices[i]->parent == -2)
        {
            graph->lsvertices[i]->parent = -1;
            dfs_visit(graph, i);
            insertbegin(graph->lsvertices[i]->vertex);
        }
    }
}

int main(int argc, char *argv[]) // main function
{
    // if (argc != 2)
    // {
    //     printf("Please give correct number(2) of command line inputs!\n");
    // }
    FILE *fp, *output;
    fp = fopen(argv[1], "r");
    output = fopen("ts.txt", "w");
    if (fp == NULL)
    {
        printf("Couldn't open input file, sorry try again!\n");
    }
    if (output == NULL)
    {
        printf("Couldn't open ts.txt,sorry try again!\n");
    }
    int num_vertices, num_edges, v1, v2;
    fscanf(fp, "%d %d", &num_vertices, &num_edges);
    Graph *graph = creategraph(num_vertices);
    while (fscanf(fp, "%d %d", &v1, &v2) != EOF)
    {
        addedge(graph, v1, v2);
    }
    dfs(graph, num_vertices);
    node *temp = topo_sort;
    int i = 0;
    while (temp != NULL)
    {
        fprintf(output, "%d\n", temp->vertex);
        temp = temp->next;
        i++;
    }
    fclose(fp);
    fclose(output);
    return 0;
}