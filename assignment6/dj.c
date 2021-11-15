/* C Program to find Shortest Distances or Path using Dijkstra's algorithm */

#include <stdio.h>

#define MAX 100
#define TEMP 0
#define PERM 1
#define infinity 9999
#define NIL -1

void findPath(int s, int v);
void Dijkstra(int s);
int min_temp();
void create_graph();

int n; /* Denotes number of vertices in the graph */
int adj[MAX][MAX];
int predecessor[MAX]; /*predecessor of each vertex in shortest path*/
int pathLength[MAX];
int status[MAX];

int main()
{
  int s, v;

  create_graph();
  while (1)
  {

    printf("\nEnter source vertex : ");
    scanf("%d", &s);

    Dijkstra(s);

    while (1)
    {
      printf("\nEnter destination vertex(-1 to quit): ");
      scanf("%d", &v);
      if (v == -1)
        break;
      if (v < 0 || v >= n)
        printf("\nThis vertex does not exist\n");
      else if (v == s)
        printf("\nSource and destination vertices are same\n");
      else if (pathLength[v] == infinity)
        printf("\nThere is no path from source to destination vertex\n");
      else
        findPath(s, v);
    }
    if (s == -1)
    {
      break;
    }
  }
  return 0;
} /*End of main()*/

void Dijkstra(int s)
{
  int i, current;

  /* Make all vertices temporary */
  for (i = 0; i < n; i++)
  {
    predecessor[i] = NIL;
    pathLength[i] = infinity;
    status[i] = TEMP;
  }
  /* Make pathLength of source vertex equal to 0 */
  pathLength[s] = 0;

  while (1)
  {
    /*Search for temporary vertex with minimum pathLength
                and make it current vertex*/
    current = min_temp();

    if (current == NIL)
      return;

    status[current] = PERM;

    for (i = 0; i < n; i++)
    {
      /*Checks for adjacent temporary vertices */
      if (adj[current][i] != 0 && status[i] == TEMP)
        if (pathLength[current] + adj[current][i] < pathLength[i])
        {
          predecessor[i] = current; /*Relabel*/
          pathLength[i] = pathLength[current] + adj[current][i];
        }
    }
  }
} /*End of Dijkstra( )*/

/*Returns the temporary vertex with minimum value of pathLength
  Returns NIL if no temporary vertex left or
  all temporary vertices left have pathLength infinity*/
int min_temp()
{
  int i;
  int min = infinity;
  int k = NIL;
  for (i = 0; i < n; i++)
  {
    if (status[i] == TEMP && pathLength[i] < min)
    {
      min = pathLength[i];
      k = i;
    }
  }
  return k;
} /*End of min_temp( )*/

void findPath(int s, int v)
{
  int i, u;
  int path[MAX];     /*stores the shortest path*/
  int shortdist = 0; /*length of shortest path*/
  int count = 0;     /*number of vertices in the shortest path*/

  /*Store the full path in the array path*/
  while (v != s)
  {
    count++;
    path[count] = v;
    u = predecessor[v];
    shortdist += adj[u][v];
    v = u;
  }
  count++;
  path[count] = s;

  printf("\nShortest Path is : ");
  for (i = count; i >= 1; i--)
    printf("%d  ", path[i]);
  printf("\nShortest distance is : %d\n", shortdist);
} /*End of findPath()*/

void create_graph()
{
  int i, max_edges, origin, destin, wt;

  printf("\nEnter number of vertices : ");
  scanf("%d", &n);
  max_edges = n * (n - 1);

  for (i = 1; i <= max_edges; i++)
  {
    printf("\nEnter edge %d( -1 -1 to quit ) : ", i);
    scanf("%d %d", &origin, &destin);

    if ((origin == -1) && (destin == -1))
      break;

    printf("\nEnter weight for this edge : ");
    scanf("%d", &wt);

    if (origin >= n || destin >= n || origin < 0 || destin < 0)
    {
      printf("\nInvalid edge!\n");
      i--;
    }
    else
      adj[origin][destin] = wt;
  }
}