#include <bits/stdc++.h>
using namespace std;
int G[100][100];
int in[1000] = {0};

#include <stdlib.h>
#define SIZE 40

struct queueu
{
  int items[SIZE];
  int front;
  int rear;
};

struct queueu *createQueue();
void enqueue(struct queueu *q, int);
int dequeue(struct queueu *q);
void display(struct queueu *q);
int isEmpty(struct queueu *q);
void printQueue(struct queueu *q);

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
  struct queueu *q = createQueue();

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
struct queueu *createQueue()
{
  struct queueu *q = malloc(sizeof(struct queueu));
  q->front = -1;
  q->rear = -1;
  return q;
}

// Check if the queue is empty
int isEmpty(struct queueu *q)
{
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

// Adding elements into queue
void enqueue(struct queueu *q, int value)
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
int dequeue(struct queueu *q)
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
void printQueue(struct queueu *q)
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
  cin >> n;
  int edges;
  cin >> edges;
  while (edges--)
  {

    int x, y;
    cin >> x >> y;
    G[x][in[x]] = y;
    G[y][in[y]] = x;
    in[x]++;
    in[y]++;
  }
  int visited[n] = {0};

  int d[n], p[n];
  int s = 0;
  visited[s] = 1;
  d[s] = 0;
  p[s] = -1;
  // queue<int> q;
  // int q[1000];
  int q_index = 0;
  // q.push(s);
  // q[q_index] = s;
  struct queueu *q = createQueue();
  enqueue(q, s);
  // int i = 0;
  while (!isEmpty(q))
  {
    int v = dequeue(q);
    // q.pop();
    for (int u : G[v])
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
    }
  }

  for (int i = 0; i < n; i++)
  {
    cout << d[i] << " ";
  }
  cout << endl;

  return 0;
}