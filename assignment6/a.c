#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int length = 0;
struct node
{
  int data;
  struct node *next;
};

struct node *head = NULL;
struct vertex
{
  int colour;
  int pred;
  int distance;
};

struct node *create_node()
{
  struct node *newnode = (struct node *)malloc(sizeof(struct node));
  if (newnode == NULL)
  {
    exit(0);
  }
  newnode->next = NULL;
  return newnode;
}

void enqueue(int data)
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
  length++;
}

int dequeue()
{
  struct node *traversal;
  int data;
  if (head == NULL)
  {
    exit(0);
  }
  else if (head->next == NULL)
  {
    data = head->data;
    head = NULL;
    length--;
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
    length--;
    return data;
  }
}
int isEmpty()
{
  if (head == NULL)
  {
    return 1;
  }
  return 0;
}

int main()
{
  int edges, vertices;
  // struct node *
  int x, y;
  FILE *input;
  input = fopen("Assignment#6-io/input1.graph", "r");
  fscanf(input, "%d %d", &vertices, &edges);

  int **adj = (int **)malloc(vertices * sizeof(int *));

  for (int i = 0; i < vertices; i++)
  {
    adj[i] = (int *)malloc(vertices * sizeof(int));
  }

  struct vertex *vert = (struct vertex *)malloc(vertices * sizeof(struct vertex));

  for (int i = 0; i < vertices; i++)
  {
    for (int j = 0; j < vertices; j++)
    {
      adj[i][j] = 0;
    }
  }

  while (fscanf(input, "%d %d", &x, &y) != EOF)
  {
    adj[x][y] = 1;
    adj[y][x] = 1;
  }
}
