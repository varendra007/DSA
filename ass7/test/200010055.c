#include <stdio.h>
#include <stdlib.h>

struct vertex
{
  int c;
  int p;
  int n;
  int t;
  int t_;
} * vert;

struct node
{
  int data;
  struct node *next;
} * head;

int V, E;
int **adj;
// __INT32_MAX__

int t = 0;

struct node *createNode()
{

  struct node *newNode = (struct node *)malloc(sizeof(struct node));

  if (newNode == NULL)
  {
    printf("\nCannot allocate memory for the new node\n");
    exit(0);
  }

  newNode->next = NULL;

  return newNode;
}

void insertNode(int data)
{
  struct node *newNode, *temp;
  newNode = createNode();

  newNode->data = data;

  if (head == NULL)
  {
    head = newNode;
  }

  else
  {
    temp = head;
    head = newNode;
    newNode->next = temp;
  }
}

void dfs(int d)
{
  t = t + 1;
  vert[d].t_ = t;
  vert[d].c = 2;

  for (int i = 0; i < V; i++)
  {
    if (adj[d][i] == 1 && vert[i].c == 1)
    {
      dfs(i);
    }
  }

  vert[d].c = 3;
  t = t + 1;
  vert[d].t = t;
}

int main(int argc, char *argv[])
{
  FILE *fp1;
  fp1 = fopen(argv[1], "r");
  if (fp1 == NULL)
  {
    printf("Please Enter correct INput file!");
    exit(1);
  }
  fscanf(fp1, "%d %d", &V, &E);
  int x, y;

  vert = (struct vertex *)malloc(V * sizeof(struct vertex));

  adj = (int **)malloc(V * sizeof(int *));

  for (int i = 0; i < V; i++)
  {
    adj[i] = (int *)malloc(V * sizeof(int));
  }

  for (int j = 0; j < V; j++)
  {
    for (int k = 0; k < V; k++)
    {
      adj[j][k] = 0;
    }
  }

  for (int i = 0; i < V; i++)
  {
    vert[i].c = 1;
    vert[i].p = -1;
    vert[i].n = -1;
    vert[i].t = -1;
  }

  for (int i = 0; i < E; i++)
  {
    fscanf(fp1, "%d %d", &x, &y);
    adj[x][y] = 1;
  }

  for (int k = 0; k < V; k++)
  {
    adj[k][k] = 0;
  }

  t = 0;

  for (int i = 0; i < V; i++)
  {

    if (vert[i].c == 1)
    {

      dfs(i);
    }
  }
  int n_ = 0;
  for (int i = 0; i < V; i++)
  {
    int m_ = INT_MAX;
    int i_ = -1;
    for (int j = 0; j < V; j++)
    {
      if (vert[j].t < m_ && vert[j].n == -1)
      {
        m_ = vert[j].t;
        i_ = j;
      }
    }
    vert[i_].n = n_;
    n_++;
    insertNode(i_);
  }

  // struct node *traversal;
  // traversal = head;
  FILE *fp2;
  fp2 = fopen("ts.txt", "w");
  if (fp2 == NULL)
  {
    printf("Unable to write in ts.txt");
  }
  while (head != NULL)
  {

    fprintf(fp2, "%d\n", head->data);

    head = head->next;
  }
  fclose(fp1);
  fclose(fp2);
  return 0;
}