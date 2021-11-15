

#include <stdio.h>
#include <stdlib.h>
struct Queue
{
  int size;
  int front;
  int rear;
  int *Q;
};

#define MAX 2000
#define TEMP 0
#define PERM 1
// #define INT_MAX 11475
#define NIL -1

int n; //Vertices
int adj[MAX][MAX];
int predecessor[MAX];
int pathLength[MAX];
int status[MAX];
struct Queue *q;

void create(int size)
{
  q->size = size;
  q->front = q->rear = -1;
  q->Q = (int *)malloc(q->size * sizeof(int));
}

struct Node
{
  int data;
  struct Node *next;

} *front = NULL, *rear = NULL;
void enqueue(int x)
{
  struct Node *t;
  t = (struct Node *)malloc(sizeof(struct Node));
  if (t == NULL)
    printf("Queue is FUll\n");
  else
  {
    t->data = x;
    t->next = NULL;
    if (front == NULL)
      front = rear = t;
    else
    {
      rear->next = t;
      rear = t;
    }
  }
}
int dequeue()
{
  int x = -1;
  struct Node *t;

  if (front == NULL)
    printf("Queue is Empty\n");
  else
  {
    x = front->data;
    t = front;
    front = front->next;
    free(t);
  }
  return x;
}
int isEmpty()
{
  return front == NULL;
}

void BFS(int start, int n)
{
  int i = start, j;

  int visited[7] = {0};

  printf("%d ", i);
  visited[i] = 1;
  enqueue(i);

  while (!isEmpty())
  {
    i = dequeue();
    for (j = 1; j < n; j++)
    {
      if (adj[i][j] == 1 && visited[j] == 0)
      {
        printf("%d ", j);
        visited[j] = 1;
        enqueue(j);
      }
    }
  }
}
void DFS(int start, int n)
{
  static int visited[7] = {0};
  int j;

  if (visited[start] == 0)
  {
    printf("%d ", start);
    visited[start] = 1;

    for (j = 1; j < n; j++)
    {
      if (adj[start][j] == 1 && visited[j] == 0)
        DFS(j, n);
    }
  }
}

void create_graph(FILE *fp)
{
  int edges, x, y;

  fscanf(fp, "%d %d\n", &n, &edges);
  for (int i = 0; i < edges; i++)
  {
    fscanf(fp, "%d %d\n", &x, &y);

    adj[x][y] = 1;
    adj[y][x] = 1;
  }
  fclose(fp);
}
int main()
{

  FILE *input;
  input = fopen("test/input1.graph", "r");
  // int s = 0, v;
  create_graph(input);

  int G[7][7] = {{0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 1, 1, 0, 0, 0},
                 {0, 1, 0, 0, 1, 0, 0},
                 {0, 1, 0, 0, 1, 0, 0},
                 {0, 0, 1, 1, 0, 1, 1},
                 {0, 0, 0, 0, 1, 0, 0},
                 {0, 0, 0, 0, 1, 0, 0}};
  DFS(4, 7);

  return 0;
}