// BFS algorithm in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 2000
int len = 0;
struct queue
{
  int items[SIZE];
  int front;
  int rear;
};

struct vertex
{
  int colour;      // white=1, grey=2, black=3
  int predecessor; // previous node in BFS
  int distance;    // distance from source vertex
};
struct queue *q;
struct queue *createQueue();
void enqueue(int);
int dequeue();
void display();
int isEmpty();
void printQueue();

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
  q = createQueue();

  graph->visited[startVertex] = 1;
  enqueue(startVertex);

  while (!isEmpty())
  {
    // printQueue(q);
    int currentVertex = dequeue();
    // printf("Visited %d\n", currentVertex);

    struct node *temp = graph->adjLists[currentVertex];

    while (temp)
    {
      int adjVertex = temp->vertex;

      if (graph->visited[adjVertex] == 0)
      {
        graph->visited[adjVertex] = 1;
        enqueue(adjVertex);
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
  q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

// Check if the queue is empty
int isEmpty()
{
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

// Adding elements into queue
void enqueue(int value)
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
  len++;
}

// Removing elements from queue
int dequeue()
{
  int item;
  if (isEmpty())
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
      // printf("Resetting queue ");
      q->front = q->rear = -1;
    }
    len--;
  }
  return item;
}

// Print the queue
void printQueue()
{
  int i = q->front;

  if (isEmpty())
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
  // struct Graph *graph = createGraph(6);
  // addEdge(graph, 0, 1);
  // addEdge(graph, 0, 2);
  // addEdge(graph, 1, 2);
  // addEdge(graph, 1, 4);
  // addEdge(graph, 1, 3);
  // addEdge(graph, 2, 4);
  // addEdge(graph, 3, 4);

  // bfs(graph, 0);
  FILE *fp;
  fp = fopen("Assignment#6-io/input2.graph", "r+");

  int vert, edges;

  fscanf(fp, "%d %d\n", &vert, &edges);

  int **adj = (int **)malloc(vert * sizeof(int *));

  for (int i = 0; i < vert; i++)
  {
    adj[i] = (int *)malloc(vert * sizeof(int));
  }

  int *distances = (int *)malloc(vert * sizeof(int));

  int *count = (int *)malloc(vert * sizeof(int *));

  struct Graph *graph = createGraph(vert);

  // for (int i = 0; i < edges; i++)
  // {
  //   int x, y;
  //   fscanf(fp, "%d %d\n", &x, &y);
  //   addEdge(graph, x, y);
  // }

  struct vertex *vertices = (struct vertex *)malloc(vert * sizeof(struct vertex));

  for (int i = 0; i < vert; i++)
  {
    for (int j = 0; j < vert; j++)
    {
      adj[i][j] = 0;
    }
  }
  int x, y;
  while (fscanf(fp, "%d %d", &x, &y) != EOF)
  {
    adj[x][y] = 1;
    adj[y][x] = 1;

    count[x]++;
    count[y]++;
  }

  for (int i = 1; i < vert; i++)
  {
    vertices[i].colour = 1;
    vertices[i].distance = -1;
    vertices[i].predecessor = -1;
  }

  vertices[0].colour = 2;
  vertices[0].distance = 0;
  vertices[0].predecessor = __INT_MAX__;

  int current_node = 0;

  enqueue(0);

  while (len)
  {
    current_node = dequeue();

    for (int i = 0; i < vert; i++)
    {
      if (adj[current_node][i])
      {
        if (vertices[i].colour == 1)
        {
          vertices[i].colour = 2;
          vertices[i].distance = vertices[current_node].distance + 1;
          vertices[i].predecessor = current_node;

          enqueue(i);
        }
      }
    }

    vertices[current_node].colour = 3;
  }
  FILE *sd;
  sd = fopen("Assignment#6-io/sd.txt", "w");

  for (int i = 0; i < vert; i++)
  {
    fprintf(sd, "%d\n", vertices[i].distance);
  }

  fclose(fp);
  fclose(sd);
  return 0;
}