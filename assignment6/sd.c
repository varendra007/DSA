// #include <bits/stdc++.h>
// using namespace std;
#include <stdio.h>
#include <stdlib.h>
int G[2000][2000];
int in[2000] = {0};

#include <stdlib.h>
#define SIZE 40000

struct queue
{
  int items[SIZE];
  int front;
  int rear;
};

struct queue *createQueue();
void enqueue(struct queue *q, int);
int dequeue(struct queue *q);
void display(struct queue *q);
int isEmpty(struct queue *q);
void printQueue(struct queue *q);

struct node
{
  int vertex;
  struct node *next;
};

struct node *createNode(int);

struct Graph
{
  int numVertices;
  struct node **adjLists;
  int *visited;
};

// BFS algorithm
void bfs(struct Graph *graph, int startVertex)
{
  struct queue *q = createQueue();

  graph->visited[startVertex] = 1;
  enqueue(q, startVertex);

  while (!isEmpty(q))
  {
    printQueue(q);
    int currentVertex = dequeue(q);
    // printf("Visited %d\n", currentVertex);

    struct node *temp = graph->adjLists[currentVertex];

    while (temp)
    {
      int adjVertex = temp->vertex;

      if (graph->visited[adjVertex] == 0)
      {
        graph->visited[adjVertex] = 1;
        enqueue(q, adjVertex);
      }
      temp = temp->next;
    }
  }
}

// Creating a node
struct node *createNode(int v)
{
  struct node *newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Creating a graph
struct Graph *createGraph(int vertices)
{
  struct Graph *graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node *));
  graph->visited = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++)
  {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }

  return graph;
}

// Add edge
void addEdge(struct Graph *graph, int src, int dest)
{
  // Add edge from src to dest
  struct node *newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  // Add edge from dest to src
  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

// Create a queue
struct queue *createQueue()
{
  struct queue *q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

// Check if the queue is empty
int isEmpty(struct queue *q)
{
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

// Adding elements into queue
void enqueue(struct queue *q, int value)
{
  if (q->rear == SIZE - 1)
    printf("\nQueue is Full!!");
  else
  {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

// Removing elements from queue
int dequeue(struct queue *q)
{
  int item;
  if (isEmpty(q))
  {
    printf("Queue is empty");
    item = -1;
  }
  else
  {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear)
    {
      printf("Resetting queue ");
      q->front = q->rear = -1;
    }
  }
  return item;
}

// Print the queue
void printQueue(struct queue *q)
{
  int i = q->front;

  if (isEmpty(q))
  {
    printf("Queue is empty");
  }
  else
  {
    printf("\nQueue contains \n");
    for (i = q->front; i < q->rear + 1; i++)
    {
      printf("%d ", q->items[i]);
    }
  }
}

int main()
{
  int n;
  // cin >> n;
  scanf("%d", &n);
  int edges;
  // cin >> edges;
  scanf("%d", &edges);
  int vertices[n];
  int ver_index = 0;
  while (edges--)
  {

    int x, y;
    // cin >> x >> y;
    scanf("%d", &x);
    scanf("%d", &y);
    G[x][in[x]] = y;
    G[y][in[y]] = x;
    vertices[ver_index] = y;
    ver_index++;
    in[x]++;
    in[y]++;
  }
  int visited[n];
  for (int i = 0; i < n; i++)
  {
    visited[i] = 0;
  }

  int d[n], p[n];
  int s = 0;
  visited[s] = 1;
  d[s] = 0;
  p[s] = -1;
  for (int i = 0; i < 100; i++)
  {
    d[i] = 1000;
  }
  // queue<int> q;
  // int q[1000];
  int q_index = 0;
  // q.push(s);
  // q[q_index] = s;
  struct queue *q = createQueue();
  enqueue(q, s);
  // int i = 0;
  while (!isEmpty(q))
  {
    int v = dequeue(q);
    // q.pop();
    /* for (int u : G[v])
    {

      if (!visited[u])
      {
        visited[u] = 1;
        // q.push(u);
        enqueue(q, u);
        d[u] = d[v] + 1;
        p[u] = v;
        // i++;
      }
    } */

    for (int i = 0; i < 100; i++)
    {
      int u = G[v][i];
      if (!visited[u])
      {
        visited[u] = 1;
        enqueue(q, u);
        d[u] = d[v] + 1;
        p[u] = v;
      }
    }
  }

  for (int i = 0; i < n; i++)
  {
    // cout << d[i] << " ";
    printf("%d ", vertices[i]);
    // printf("%d ", d[i]);
  }
  // cout << endl;
  printf("\n");
  for (int i = 0; i < 6; i++)
  {
    // cout << d[i] << " ";
    // printf("%d ", vertices[i]);
    // if (d[i] == 1000)
    // {
    //   printf("-1 ");
    // }
    // else
    // {
    printf("1");

    printf("%d ", d[i]);
    // }
  }
  // cout << endl;
  printf("\n");

  return 0;
}