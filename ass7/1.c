#include <stdio.h>

#include <conio.h>

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
  // n = edges;
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
    // adj[y][x] = 1;
  }
  fclose(fp);
}

int main(int argc, char *argv[])
{

  int i, j, k, n, indeg[MAX], flag[MAX], count = 0;

  // printf("Enter the no of vertices:\n");

  // scanf("%d", &n);

  // printf("Enter the adjacency matrix:\n");

  // for (i = 0; i < n; i++)
  // {

  //   printf("Enter row %d\n", i + 1);

  //   for (j = 0; j < n; j++)

  //     scanf("%d", &a[i][j]);
  // }

  FILE *out, *inp;

  // inp = fopen(argv[1], "r");
  inp = fopen("test/input1.graph", "r");
  if (inp == NULL)
  {
    printf("lafkdsfj");
  }
  create_graph(inp);

  for (int i = 0; i < 10; i++)
  {
    printf("%d ", &adj[i][0]);
  }

  out = fopen("out.txt", "w+");
  if (out == NULL)
  {
    printf("lakjdfladf");
  }

  for (i = 0; i < n; i++)
  {

    indeg[i] = 0;

    flag[i] = 0;
  }

  for (i = 0; i < n; i++)

    for (j = 0; j < n; j++)

      indeg[i] = indeg[i] + adj[j][i];

  // printf("\nThe topological order is:");

  while (count < n)
  {

    for (k = 0; k < n; k++)
    {

      // printf("lakdf");
      if ((indeg[k] == 0) && (flag[k] == 0))
      {

        // printf("alkdf");
        fprintf(out, "%d\n", (k + 1));

        flag[k] = 1;
      }

      for (i = 0; i < n; i++)
      {

        if (adj[i][k] == 1)

          indeg[k]--;
      }
    }

    count++;
  }

  fclose(out);
  return 0;
}
