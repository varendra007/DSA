
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void BellmanFord(int graph[][3], int V, int E, int src)
{
  int dis[V];
  for (int i = 0; i < V; i++)
    dis[i] = INT_MAX;

  dis[src] = 0;

  for (int i = 0; i < V - 1; i++)
  {

    for (int j = 0; j < E; j++)
    {
      if (dis[graph[j][0]] != INT_MAX && dis[graph[j][0]] + graph[j][2] < dis[graph[j][1]])
      {
        dis[graph[j][1]] = dis[graph[j][0]] + graph[j][2];
      }
    }
  }

  for (int i = 0; i < E; i++)
  {
    int x = graph[i][0];
    int y = graph[i][1];
    int weight = graph[i][2];
    if (dis[x] != INT_MAX &&
        dis[x] + weight < dis[y])
    {
      // dis[i] = -1000;
    }
  }

  FILE *fp1;
  fp1 = fopen("sd.txt", "w");
  for (int i = 0; i < V; i++)
  {
    fprintf(fp1, "%d ", i);
    if (dis[i] >= INT_MAX)
    {
      fprintf(fp1, "+inf\n");
    }
    else if (dis[i] <= -100)
    {
      fprintf(fp1, "-inf\n");
    }
    else
    {
      fprintf(fp1, "%d\n", dis[i]);
    }
  }

  fclose(fp1);
}

int main(int argc, char *argv[])
{
  int V = 5;
  int E = 8;
  int S;

  FILE *fp;
  fp = fopen(argv[1], "r");
  if (fp == NULL)
  {
  }
  fscanf(fp, "%d %d", &V, &E);

  S = 0;

  int graph[E][3];
  for (int i = 0; i < E; i++)
  {
    fscanf(fp, "%d %d %d", &graph[i][0], &graph[i][1], &graph[i][2]);
  }

  BellmanFord(graph, V, E, S);
  return 0;
}