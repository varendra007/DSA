#include <bits/stdc++.h>

using namespace std;

struct t
{
  int x;
  int y;
};

int main()
{
  FILE *f;
  f = fopen("dijkstra2.txt", "r");
  vector<pair<int, int>> v;
  int x, y;
  while (fscanf(f, "%d %d", &x, &y) != EOF)
  {
    v.push_back(make_pair(x, y));
  }

  // sort(v, v.end() - 1);
  sort(v.begin(), v.end());

  FILE *fp = fopen("ut1.txt", "w");
  for (auto T : v)
  {
    // cout << T.first << " " << T.second << endl;
    fprintf(fp, "%d %d\n", T.first, T.second);
  }
}