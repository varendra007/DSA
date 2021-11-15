// A C++ program to print topological sorting of a DAG
#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Graph
{
  int V;

  list<int> *adj;

  void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);

public:
  Graph(int V);
  void addEdge(int v, int w);

  void topologicalSort();
};

Graph::Graph(int V)
{
  this->V = V;
  adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
  adj[v].push_back(w);
}

void Graph::topologicalSortUtil(int v, bool visited[],
                                stack<int> &Stack)
{

  visited[v] = true;

  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      topologicalSortUtil(*i, visited, Stack);

  Stack.push(v);
}

void Graph::topologicalSort()
{
  FILE *out;
  out = fopen("out.txt", "w+");
  stack<int> Stack;

  // Mark all the vertices as not visited
  bool *visited = new bool[V];
  for (int i = 0; i < V; i++)
    visited[i] = false;

  for (int i = 0; i < V; i++)
    if (visited[i] == false)
      topologicalSortUtil(i, visited, Stack);

  while (Stack.empty() == false)
  {
    // cout << Stack.top() << " ";
    fprintf(out, "%d\n", Stack.top());
    Stack.pop();
  }
}

int main()
{

  FILE *out, *inp;

  // inp = fopen(argv[1], "r");
  inp = fopen("test/input1.graph", "r");
  if (inp == NULL)
  {
    printf("lafkdsfj");
  }
  // create_graph(inp);

  // for (int i = 0; i < 10; i++)
  // {
  //   printf("%d ", &adj[i][0]);
  // }

  out = fopen("out.txt", "w+");
  if (out == NULL)
  {
    printf("lakjdfladf");
  }
  int n, edges, v1, v2;
  // cin >> n;
  fscanf(inp, "%d %d", &n, &edges);
  Graph g(edges);
  for (int i = 1; i <= edges; i++)
  {
    // cin >> v1 >> v2;
    fscanf(inp, "%d %d", &v1, &v2);
    g.addEdge(v1, v2);
  }

  // cout << " Topological Sort of the given graph \n";
  g.topologicalSort();

  return 0;
}
