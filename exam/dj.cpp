#include <stdio.h>
#include <conio.h>
// #include <bits/stdc++.h>
// using namespace std;
#define INT_MAX 9999
#define MAX 130

void dijkstra(int G[MAX][MAX], int n, int startnode);

int main()
{
  int G[MAX][MAX], i, j, n, u;
  int w;

  n = 130;

  FILE *p = fopen("test/input.graph", "r");

  while (fscanf(p, "%d %d %d", &i, &j, &w) != EOF)
  {
    // if (i != j)
    // {

    if (G[i][j] == 0)
      G[i][j] = w;
    // }
  }

  u = 14;
  dijkstra(G, n, u);
  return 0;
}

void dijkstra(int G[MAX][MAX], int n, int startnode)
{

  int cost[MAX][MAX], distance[MAX], pred[MAX];
  int visited[MAX], count, mindistance, nextnode, i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    // if (i != j)
    {

      if (G[i][j] == 0)
        cost[i][j] = INT_MAX;
      else
        cost[i][j] = G[i][j];
    }
  // else
  {
    // cost[i][j] = INT_MAX;
  }
  //initialize pred[],distance[] and visited[]
  for (i = 0; i < n; i++)
  {
    distance[i] = cost[startnode][i];
    pred[i] = startnode;
    visited[i] = 0;
  }
  distance[startnode] = 0;
  visited[startnode] = 1;
  count = 1;
  while (count < n - 1)
  {
    mindistance = INT_MAX;
    //nextnode gives the node at minimum distance
    for (i = 0; i < n; i++)
      if (distance[i] < mindistance && !visited[i])
      {
        mindistance = distance[i];
        nextnode = i;
      }
    //check if a better path exists through nextnode
    visited[nextnode] = 1;
    for (i = 0; i < n; i++)
      if (!visited[i])
        if (mindistance + cost[nextnode][i] < distance[i])
        {
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode;
        }
    count++;
  }

  //print the path and distance of each node
  FILE *f = fopen("ss.txt", "w");
  for (i = 0; i < n; i++)
  {
    // if (distance[i] == INT_MAX)
    // {
    //   distance[i] = -1;
    // }
    if (distance[i] < 0)
    {
      distance[i] = -1;
    }
    fprintf(f, "\n%d  %d", i, distance[i]);
  }
}