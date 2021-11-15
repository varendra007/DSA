#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20000
#define TEMP 0
#define PERM 1
#define NIL -1

int n = 0; //Vertices
int adj[MAX][MAX];

int *predecessor, *pathLength, *status;

void create_graph(FILE *fp)
{
  int w, x, y;

  while (fscanf(fp, "%d %d %d", &x, &y, &w) != EOF)
  {

    adj[x][y] = w;
  }

  fclose(fp);
}

void findPath(int s, int v, FILE *fp)
{
  int i, u;
  i = v;
  int path[MAX];
  int shortdist = 0;
  int count = 0;

  while (v != s)
  {
    count++;
    u = predecessor[v];
    shortdist += adj[u][v];
    v = u;
  }
  count++;
  if (shortdist >= INT_MAX)
  {
    fprintf(fp, "%d -1\n", i);
  }
  else
  {

    fprintf(fp, "%d %d\n", i, shortdist);
  }
}

int min_temp()
{
  int i;
  int min = INT_MAX;
  int k = NIL;
  for (int i = 0; i < n; i++)
  {
    if (status[i] == TEMP && pathLength[i] < min)
    {
      min = pathLength[i];
      k = i;
    }
  }
  return k;
}

void dj(int s)
{
  int i, current;
  for (i = 0; i < n; i++)
  {
    predecessor[i] = NIL;
    pathLength[i] = INT_MAX;
    status[i] = TEMP;
  }
  pathLength[s] = 0;
  while (1)
  {
    current = min_temp();
    if (current == NIL)
    {
      return;
    }

    status[current] = PERM;

    for (i = 0; i < n; i++)
    {
      if (adj[current][i] != 0 && status[i] == TEMP)
      {
        if (pathLength[current] + adj[current][i] < pathLength[i])
        {
          predecessor[i] = current;
          pathLength[i] = pathLength[current] + adj[current][i];
        }
      }
    }
  }
}

int main(int argc, char *argv[])
{

  FILE *input;
  input = fopen(argv[1], "r");
  int s = atoi(argv[2]);
  int v;
  v = 0;

  int w, x, y;

  while (fscanf(input, "%d %d %d", &x, &y, &w) != EOF)
  {
    if (x > y && x > n)
    {
      n = x;
    }
    else if (y > x && y > n)
    {
      n = y;
    }
  }
  n++;

  predecessor = (int *)malloc(n * sizeof(int));
  pathLength = (int *)malloc(n * sizeof(int));
  status = (int *)malloc(n * sizeof(int));

  fclose(input);

  input = fopen(argv[1], "r");
  create_graph(input);
  dj(s);
  FILE *fp;
  fp = fopen("dijkstra.txt", "w+");
  if (fp == NULL)
  {
    printf("\nUnable to write in dijkstra.txt\n");
    exit(1);
  }
  while (1)
  {

    if (v == s)
    {
      fprintf(fp, "%d 0\n", v);
    }
    else if (pathLength[v] == INT_MAX)
    {
      fprintf(fp, "%d -1\n", v);
    }
    else
    {
      findPath(s, v, fp);
    }
    if (v < n - 1)
    {
      v++;
    }
    else
    {
      break;
    }
  }
  fclose(fp);

  return 0;
}
