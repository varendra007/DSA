#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
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

void create_graph(FILE *fp)
{
  int edges, x, y;
  // FILE *fp;
  // // fp = fopen("Assignment#6-io/input3.graph", "r+");
  // if (fp == NULL)
  // {
  //   printf("\nUnable to read input file! Please enter correct path.\n");
  //   exit(1);
  // }

  fscanf(fp, "%d %d\n", &n, &edges);
  for (int i = 0; i < edges; i++)
  {
    fscanf(fp, "%d %d\n", &x, &y);

    // if (x >= n || y >= n || x < 0 || y < 0)
    // {
    //   printf("||inavalid edge!");
    // }
    // else
    // {
    //   adj[x][y] = 1;
    // }
    adj[x][y] = 1;
    adj[y][x] = 1;
  }
  fclose(fp);
}

void findPath(int s, int v, FILE *fp)
{
  int i, u;
  int path[MAX];
  int shortdist = 0;
  int count = 0;

  while (v != s)
  {
    count++;
    // path[count] = v;
    u = predecessor[v];
    shortdist += adj[u][v];
    v = u;
  }
  count++;
  // path[count] = s;

  fprintf(fp, "%d\n", shortdist);
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
  int s = 0, v;
  create_graph(input);
  dj(s);
  v = 0;
  FILE *fp;
  fp = fopen("Assignment#6-io/sd.txt", "w+");
  if (fp == NULL)
  {
    printf("\nUnable to write in sd.txt\n");
    exit(1);
  }
  while (1)
  {
    // s = 0;

    if (v == s)
    {
      // printf("0\n");
      fprintf(fp, "0\n");
    }
    else if (pathLength[v] == INT_MAX)
    {
      fprintf(fp, "-1\n");
    }
    else
    {
      findPath(s, v, fp);
    }
    // printf("%d\n", v);
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
