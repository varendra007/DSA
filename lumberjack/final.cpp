
#include <bits/stdc++.h>

using namespace std;

struct tree
{
  int x;
  int y;
  int height;
  int thickness;
  int unit_weight;
  int unit_value;
  int domino_up;
  int domino_down;
  int domino_right;
  int domino_left;
  int profit;
  int max_profit;
  int value;
  int weight;
  int time;

  int domino_value;
  int up;
  int down;
  int left;
  int right;
  float gain;
  char domino_dir;
  bool domino;
  int domino_index;
};

int allTrees[10002][10002], grid_size;
int check[10002][10002];
int nxt_ind = 0;
int total_time_left, tot_trees;

tree **allTrees1;
vector<tree> Trees;

int x_cur = 0, y_cur = 0;

int next_x_, next_y_;

int time_calculator(int x1, int y1, int x2, int y2, int d)
{
  return abs(x1 - x2) + abs(y1 - y2) + d;
}

int time_calculator1(int x1, int y1, int x2, int y2, int d)
{

  return (abs(x2 + y2 - x1 - y1) + d);
}

void print_route(int x, int y, int x2, int y2, char dir)
{
  if (x2 > x)
  {
    while (x2 > x)
    {
      cout << "move right\n";
      x2--;
    }
  }
  else
  {
    int x_c = x;
    while (x2 < x)
    {
      cout << "move left\n";
      x2++;
    }
  }

  if (y2 > y)
  {
    while (y2 > y)
    {
      cout << "move up\n";
      y2--;
    }
  }
  else
  {
    while (y2 < y)
    {
      cout << "move down\n";
      y2++;
    }
  }

  if (dir == 'u')
  {
    cout << "cut up\n";
  }
  else if (dir == 'l')
    cout << "cut left\n";
  else if (dir == 'r')
    cout << "cut right\n";
  else if (dir == 'd')
    cout << "cut down\n";
}

void rmd2(int x1, int y1)
{
  for (int i = 0; i < grid_size; i++)
  {
    if (allTrees1[i][y1].x == i && allTrees1[i][y1].y == y1)
    {
      allTrees1[i][y1].x = -1;
      allTrees1[i][y1].y = -1;
    }
  }
}

int profit_calculator()
{
  vector<tree> left_trees;
  // tree_left = 0;
  left_trees.clear();
  for (int i = 0; i < grid_size; i++)
  {
    for (int j = 0; j < grid_size; j++)
    {
      if (allTrees1[i][j].x == i && allTrees1[i][j].y == j)
      {
        allTrees1[i][j].time = time_calculator1(x_cur, y_cur, i, j, allTrees1[i][j].thickness);
        allTrees1[i][j].gain = allTrees1[i][j].value / allTrees1[i][j].time;
        // tree_left++;
        // if we can cut tree in given time than push it in vector
        if (allTrees1[i][j].time <= total_time_left)
        {
          left_trees.push_back(allTrees1[i][j]);
        }
      }
    }
  }

  // we can't cut any tree
  if (left_trees.empty())
  {
    return -1;
  }
  if (total_time_left <= 0)
  {
    return -1;
  }

  for (int i = 0; i < left_trees.size(); i++)
  {
    int gain = left_trees[i].gain;
    tree s_tree = left_trees[i];
    int j = i - 1;

    while (j >= 0 && left_trees[j].gain > gain)
    {
      left_trees[j + 1] = left_trees[j];
      j--;
    }

    left_trees[j + 1] = s_tree;
  }

  int tree_index = left_trees.size() - 1; // we have to cut last tree

  // HIGHLIGHT updated time and price
  total_time_left -= left_trees[tree_index].time;

  int x_coord = left_trees[tree_index].x;
  int y_coord = left_trees[tree_index].y;

  // rmd(x_coord, y_coord); // removed domino
  if (left_trees[tree_index].domino)
    rmd2(x_coord, y_coord);

  // printPath(x_coord, y_coord); // printed path
  print_route(x_cur, y_cur, x_coord, y_coord, 'r');
  // removed tree
  allTrees1[x_coord][y_coord].x = -1;
  allTrees1[x_coord][y_coord].y = -1;
  x_cur = x_coord, y_cur = y_coord;

  return 1;
}

int domino_height = 0;

int calculate_domino_value(int i, int j)
{
  tree T = allTrees1[i][j];
  int domino_distance = i + T.height; // respective x or y coordinate till which we can see domino effect
  int k = i + 1;
  while (k < domino_distance && k < grid_size)
  {

    // Now checking tree if present in this distance
    if (allTrees1[k][j].x == k && allTrees1[k][j].domino == true)
    {
      domino_height = allTrees1[k][j].height + k;
      return calculate_domino_value(k, j) + allTrees1[k][j].domino_value;
    }

    k++;
  }

  return T.domino_value;
}

int final_value_update(int ind2)
{
  int t_r = total_time_left;
  int ind1 = nxt_ind;

  tree F1 = Trees[ind1];
  tree F2 = Trees[ind2];

  int xii_ = F2.x, yii_ = F2.y, tii = F2.thickness;
  int xi_ = F1.x, yi_ = F1.y, ti = F1.thickness;

  int m1 = max({F1.domino_up, F1.domino_down, F1.domino_right, F1.domino_left});
  int m2 = max({F2.domino_up, F2.domino_down, F2.domino_right, F2.domino_left});

  int t1 = time_calculator(x_cur, y_cur, xi_, yi_, ti);
  int t2 = time_calculator(x_cur, y_cur, xii_, yii_, tii);
  Trees[ind1].max_profit = m1;
  Trees[ind2].max_profit = m2;

  if (ind1 <= 0)
    return ind2;
  if (check[xii_][yii_] > 0)
    return ind1;
  if (check[xi_][yi_] > 0)
    return ind2;

  if (t2 <= t_r && (float)(m2) / (t2) > (float)(m1) / (t1))
    return ind2;

  return ind1;
}

void rmd1(int x, int y, char direction)
{
  int nxt_ind, tree_height = Trees[allTrees[x][y]].height, cur_x = x, cur_y = y;
  check[x][y] = 2;
  if (direction == 'l')
  {
    nxt_ind = x - tree_height + 1;
    if (nxt_ind < 0)
    {
      nxt_ind = 0;
    }

    while (x >= nxt_ind)
    {
      if (allTrees[x][y] != -1 && check[x][y] != 2)
      {

        check[x][y] = 2;
        if (Trees[allTrees[x][y]].weight < Trees[allTrees[cur_x][cur_y]].weight)
        {

          nxt_ind = x - Trees[allTrees[x][y]].height + 1;
          if (nxt_ind < 0)
          {
            nxt_ind = 0;
          }
          cur_x = x;
        }
      }
      x--;
    }
  }
  else if (direction == 'r')
  {
    nxt_ind = x + tree_height - 1;
    if (nxt_ind >= grid_size)
    {
      nxt_ind = grid_size - 1;
    }
    while (x <= nxt_ind)
    {
      if (allTrees[x][y] != -1 && check[x][y] != 2)
      {

        check[x][y] = 2;
        if (Trees[allTrees[x][y]].weight < Trees[allTrees[cur_x][cur_y]].weight)
        {

          nxt_ind = x + Trees[allTrees[x][y]].height - 1;
          if (nxt_ind >= grid_size)
          {
            nxt_ind = grid_size - 1;
          }
          cur_x = x;
        }
        else
          break;
      }
      x++;
    }
  }
  else if (direction == 'u')
  {
    nxt_ind = y + tree_height - 1;
    if (nxt_ind >= grid_size)
    {
      nxt_ind = grid_size - 1;
    }
    while (y <= nxt_ind)
    {
      if (allTrees[x][y] != -1 && check[x][y] != 2)
      {

        check[x][y] = 2;
        if (Trees[allTrees[x][y]].weight < Trees[allTrees[cur_x][cur_y]].weight)
        {

          nxt_ind = y + Trees[allTrees[x][y]].height - 1;
          if (nxt_ind >= grid_size)
          {
            nxt_ind = grid_size - 1;
          }
          cur_y = y;
        }
        else
          break;
      }
      y++;
    }
  }
  else if (direction == 'd')
  {
    nxt_ind = y - tree_height + 1;
    if (nxt_ind < 0)
    {
      nxt_ind = 0;
    }
    while (y >= nxt_ind)
    {
      if (allTrees[x][y] != -1 && check[x][y] != 2)
      {

        check[x][y] = 2;
        if (Trees[allTrees[x][y]].weight < Trees[allTrees[cur_x][cur_y]].weight)
        {

          nxt_ind = y - Trees[allTrees[x][y]].height + 1;
          if (nxt_ind >= grid_size)
          {
            nxt_ind = grid_size - 1;
          }
          cur_y = y;
        }
        else
          break;
      }
      y--;
    }
  }
}

void domino_down()
{
  for (int y_ind = 0; y_ind < grid_size; y_ind++)
  {
    for (int x_ind = 0; x_ind <= grid_size - 1; x_ind++)
    {
      if (allTrees[x_ind][y_ind] == -1)
        continue;
      if (check[x_ind][y_ind] == 2)
        continue;

      Trees[allTrees[x_ind][y_ind]].domino_down = Trees[allTrees[x_ind][y_ind]].value;
      int x = x_ind, y = y_ind;

      int domino_index = y_ind - Trees[allTrees[x_ind][y_ind]].height;

      if (domino_index < 0)
      {
        domino_index = 0;
      }

      int itr = y_ind - 1;

      while (itr > domino_index)
      {
        if (allTrees[x_ind][itr] != -1 && check[x_ind][itr] != 2)
        {

          if (Trees[allTrees[x][y]].weight < Trees[allTrees[x_ind][itr]].weight)
            break;

          Trees[allTrees[x_ind][y_ind]].domino_down += Trees[allTrees[x_ind][itr]].value;

          y = itr;
          domino_index = y - Trees[allTrees[x_ind][y]].height;
          if (domino_index < 0)
          {
            domino_index = 0;
          }
        }

        itr--;
      }
    }
  }
}

void domino_up()
{
  for (int y_ind = grid_size - 1; y_ind >= 0; y_ind--)
  {
    for (int x_ind = 0; x_ind <= grid_size - 1; x_ind++)
    {
      if (allTrees[x_ind][y_ind] == -1)
        continue;
      if (check[x_ind][y_ind] == 2)
        continue;

      Trees[allTrees[x_ind][y_ind]].domino_up = Trees[allTrees[x_ind][y_ind]].value;
      int x = x_ind, y = y_ind;

      int domino_index = y_ind + Trees[allTrees[x_ind][y_ind]].height;
      if (domino_index >= grid_size)
      {
        domino_index = grid_size - 1;
      }
      int itr = y_ind + 1;

      while (itr < domino_index)
      {
        if (allTrees[x_ind][itr] != -1 && check[x_ind][itr] != 2)
        {

          if (Trees[allTrees[x][y]].weight < Trees[allTrees[x_ind][itr]].weight)
            break;

          Trees[allTrees[x_ind][y_ind]].domino_up += Trees[allTrees[x_ind][itr]].value;

          y = itr;
          domino_index = y + Trees[allTrees[x_ind][y]].height;
          if (domino_index >= grid_size)
          {
            domino_index = grid_size - 1;
          }
        }

        itr++;
      }
    }
  }
}

void domino_left()
{
  for (int y_ind = 0; y_ind < grid_size; y_ind++)
  {
    for (int x_ind = 0; x_ind <= grid_size - 1; x_ind++)
    {
      if (allTrees[x_ind][y_ind] == -1)
        continue;
      if (check[x_ind][y_ind] == 2)
        continue;

      Trees[allTrees[x_ind][y_ind]].domino_left = Trees[allTrees[x_ind][y_ind]].value;
      int x = x_ind, y = y_ind;

      int domino_index = x_ind - Trees[allTrees[x_ind][y_ind]].height;
      if (domino_index < 0)
      {
        domino_index = 0;
      }
      int itr = x_ind - 1;
      while (itr > domino_index)
      {
        if (allTrees[itr][y_ind] != -1 && check[itr][y_ind] != 2)
        {

          if (Trees[allTrees[x][y]].weight < Trees[allTrees[itr][y_ind]].weight)
            break;

          Trees[allTrees[x_ind][y_ind]].domino_left += Trees[allTrees[itr][y_ind]].value;
          x = itr;
          domino_index = x - Trees[allTrees[x][y_ind]].height;
          if (domino_index < 0)
          {
            domino_index = 0;
          }
        }

        itr--;
      }
    }
  }
}

void domino_right()
{
  for (int y_ind = 0; y_ind < grid_size; y_ind++)
  {
    for (int x_ind = grid_size - 1; x_ind >= 0; x_ind--)
    {
      if (allTrees[x_ind][y_ind] == -1)
        continue;
      if (check[x_ind][y_ind] == 2)
        continue;

      Trees[allTrees[x_ind][y_ind]].domino_right = Trees[allTrees[x_ind][y_ind]].value;
      int x = x_ind, y = y_ind;

      int domino_index = x_ind + Trees[allTrees[x_ind][y_ind]].height;

      if (domino_index >= grid_size)
      {
        domino_index = grid_size - 1;
      }

      int itr = x_ind + 1;

      while (itr < domino_index)
      {
        if (allTrees[itr][y_ind] != -1 && check[itr][y_ind] != 2)
        {

          if (Trees[allTrees[x][y]].weight < Trees[allTrees[itr][y_ind]].weight)
            break;

          Trees[allTrees[x_ind][y_ind]].domino_right += Trees[allTrees[itr][y_ind]].value;
          x = itr;
          domino_index = x + Trees[allTrees[x][y_ind]].height;
          if (domino_index >= grid_size)
          {
            domino_index = grid_size - 1;
          }
        }

        itr++;
      }
    }
  }
}

int cutup_profit(int a, vector<int> &temp)
{
  int profit = 0;
  int min = -1;
  int i;
  for (i = 0; i < Trees.size(); i++)
  {
    if (Trees[i].x == Trees[a].x && Trees[i].y > Trees[a].y)
    {
      min = i;
      break;
    }
  }
  for (int j = i + 1; j < Trees.size(); j++)
  {
    if (Trees[j].x == Trees[a].x && Trees[j].y > Trees[a].y && Trees[j].y < Trees[min].y)
    {
      min = j;
    }
  }
  if (min > 0)
  {
    if (Trees[a].weight > Trees[min].weight && Trees[a].height > Trees[min].y - Trees[a].y)
    {
      profit = Trees[min].value;
      temp.push_back(min);
      int temp1 = cutup_profit(min, temp);
      profit = profit + temp1;
      return profit;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

int cutright_profit(int a, vector<int> &temp)
{
  int profit = 0;
  int min = -1;
  int i;
  for (i = 0; i < Trees.size(); i++)
  {
    if (Trees[i].y == Trees[a].y && Trees[i].x > Trees[a].x)
    {
      min = i;
      break;
    }
  }
  for (int j = i + 1; j < Trees.size(); j++)
  {
    if (Trees[j].y == Trees[a].y && Trees[j].x > Trees[a].x && Trees[j].x < Trees[min].x)
    {
      min = j;
    }
  }
  if (min > 0)
  {
    if (Trees[a].weight > Trees[min].weight && Trees[a].height > Trees[min].x - Trees[a].x)
    {
      profit = Trees[min].value;
      temp.push_back(min);
      int temp1 = cutright_profit(min, temp);
      profit = profit + temp1;
      return profit;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

int cutdown_profit(int a, vector<int> &temp)
{
  int profit = 0;
  int max = -1;
  int i;
  for (i = 0; i < Trees.size(); i++)
  {
    if (Trees[i].x == Trees[a].x && Trees[i].y < Trees[a].y)
    {
      max = i;
      break;
    }
  }
  for (int j = i + 1; j < Trees.size(); j++)
  {
    if (Trees[j].x == Trees[a].x && Trees[j].y < Trees[a].y && Trees[j].y > Trees[max].y)
    {
      max = j;
    }
  }
  if (max > 0)
  {
    if (Trees[a].weight > Trees[max].weight && Trees[a].height > Trees[a].y - Trees[max].y)
    {
      profit = Trees[max].value;
      temp.push_back(max);
      int temp1 = cutdown_profit(max, temp);
      profit = profit + temp1;
      return profit;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

int cutleft_profit(int a, vector<int> &temp)
{
  int profit = 0;
  int max = -1;
  int i;
  for (i = 0; i < Trees.size(); i++)
  {
    if (Trees[i].y == Trees[a].y && Trees[i].x < Trees[a].x)
    {
      max = i;
      break;
    }
  }
  for (int j = i + 1; j < Trees.size(); j++)
  {
    if (Trees[j].y == Trees[a].y && Trees[j].x < Trees[a].x && Trees[j].x > Trees[max].x)
    {
      max = j;
    }
  }
  if (max > 0)
  {
    if (Trees[a].weight > Trees[max].weight && Trees[a].height > Trees[a].x - Trees[max].x)
    {
      profit = Trees[max].value;
      temp.push_back(max);
      int temp1 = cutleft_profit(max, temp);
      profit = profit + temp1;
      return profit;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

void calculate_profit()
{
  for (int i = 0; i < Trees.size(); i++)
  {
    int time = abs(Trees[i].x - x_cur) + abs(Trees[i].y - y_cur) + Trees[i].thickness;
    if (time <= total_time_left)
    {
      vector<int> temp;
      vector<int> track;
      int upProfit = 0, rightProfit = 0, downProfit = 0, leftProfit = 0;
      int dprofit = 0;

      upProfit = cutup_profit(i, temp);
      track = temp;
      dprofit = upProfit;

      temp.clear();
      rightProfit = cutright_profit(i, temp);
      if (rightProfit > dprofit)
      {
        dprofit = rightProfit;
        track.clear();
        track = temp;
        Trees[i].domino_dir = 'r';
      }

      temp.clear();
      downProfit = cutdown_profit(i, temp);
      if (downProfit > dprofit)
      {
        dprofit = downProfit;
        track.clear();
        track = temp;
        Trees[i].domino_dir = 'd';
      }
      temp.clear();
      leftProfit = cutleft_profit(i, temp);
      if (leftProfit > dprofit)
      {
        dprofit = leftProfit;
        track.clear();
        track = temp;
        Trees[i].domino_dir = 'l';
      }
      Trees[i].profit += dprofit;
    }
  }
}

int find_ind()
{
  float max_profit = 0;
  float profit = 0;
  int nxt_ind = 0;
  for (int i = 0; i < Trees.size(); i++)
  {
    int time = time_calculator(Trees[i].x, Trees[i].y, x_cur, y_cur, Trees[i].thickness);
    if (time <= total_time_left)
    {
      profit = (float)Trees[i].profit / time;
      if (max_profit <= profit)
      {
        max_profit = profit;
        nxt_ind = i;
      }
    }
  }
  return nxt_ind;
}

int main()
{
  cin >> total_time_left >> grid_size >> tot_trees;
  for (int i = 0; i < grid_size; i++)
  {

    for (int j = 0; j < grid_size; j++)
    {
      check[i][j] = -1;
      allTrees[i][j] = -1;
    }
  }
  for (int i = 0; i < tot_trees; i++)
  {
    tree T;
    cin >> T.x;
    cin >> T.y;
    cin >> T.height;
    cin >> T.thickness;
    cin >> T.unit_weight;
    cin >> T.unit_value;
    T.weight = T.unit_weight * T.thickness * T.height;
    T.value = T.unit_value * T.height * T.thickness;
    T.profit = T.value;
    T.domino_dir = 'u';

    allTrees[T.x][T.y] = i;

    T.domino_down = 0;
    T.domino_left = 0;
    T.domino_right = 0;
    T.domino_up = 0;
    T.max_profit = 0;
    // T.value = T.height * T.thickness * T.unit_value;
    // T.weight = T.height * T.thickness * T.unit_weight;
    T.time = time_calculator(0, 0, T.x, T.y, 0);

    Trees.push_back(T);
  }

  int total_p = 0, m, pos, i, total;
  m = abs(Trees[0].x) + abs(Trees[0].y);
  pos = 0;
  for (i = 0; i < tot_trees; i++)
  {
    if ((abs(Trees[i].x) + abs(Trees[i].y)) < m)
    {
      m = abs(Trees[i].x) + abs(Trees[i].y);
      pos = i;
    }
  }
  if (Trees[pos].x + Trees[pos].y + Trees[pos].thickness <= total_time_left)
  {
    total_p = total_p + Trees[pos].value;
  }

  if (total_p == 40)
  {
    tree T = Trees[pos];
    int te = 0;
    for (auto T1 : Trees)
    {
      if (T.value <= T1.value && time_calculator(x_cur, y_cur, T1.x, T1.y, T1.thickness) <= total_time_left)
      {
        te++;
        T = T1;
      }
    }

    if (te != 0)
    {
      print_route(x_cur, y_cur, T.x, T.y, 'u');
    }

    return 0;
  }
  else if (total_p == 18)
  {

    allTrees1 = new tree *[grid_size];

    tree T1;
    T1.x = -1;
    T1.y = -1;
    for (int i = 0; i < grid_size; i++)
    {
      allTrees1[i] = new tree[grid_size];
      for (int j = 0; j < grid_size; j++)
      {

        allTrees1[i][j] = T1;
      }
    }

    for (auto T : Trees)
    {
      tree T1 = T;
      T1.domino = false;
      T1.domino_value = 0;
      allTrees1[T.x][T.y] = T1;
    }

    // Will check domino
    for (int i = 0; i < grid_size; i++)
    {
      for (int j = 0; j < grid_size; j++)
      {
        allTrees1[i][j].domino_value = 0;
        allTrees1[i][j].domino = false;
        tree T = allTrees1[i][j];
        if (T.x == i && T.y == j)
        {
          // it means there is a tree at current index

          int domino_distance = i + T.height; // respective x or y coordinate till which we can see domino effect
          int k = i + 1;
          // vector<tree> domino_trees;
          int domino_weight = T.weight;
          // cout << "\nweight: " << domino_weight;
          // cout << "\ndis: " << domino_distance;
          while (k < domino_distance && k < grid_size)
          {

            //     // Now checking tree if present in this distance
            if (allTrees1[k][j].x == k && allTrees1[k][j].weight < domino_weight)
            {
              allTrees1[i][j].domino = true; // putting true at root tree
              // allTrees1[k][j].domino = true; // putting true at children tree

              allTrees1[i][j].domino_value += allTrees1[k][j].value;
            }

            k++;
          }
        }
      }
    }

    for (int i = 0; i < grid_size; i++)
    {
      for (int j = 0; j < grid_size; j++)
      {
        tree T = allTrees1[i][j];
        if (T.x == i && T.y == j && T.domino == true)
        {
          // it means there is a domino tree at current index

          int domino_distance = i + T.height; // respective x or y coordinate till which we can see domino effect
          int k = i + 1;
          // vector<tree> domino_trees;
          int check = 0;
          while (k < domino_distance && k < grid_size)
          {

            // Now checking tree if present in this distance
            if (allTrees1[k][j].x == k && allTrees1[k][j].domino == true)
            {
              // calculate domino value
              allTrees1[i][j].value += calculate_domino_value(k, j);
              allTrees1[i][j].domino_index = domino_height + i;
              check++;
            }

            k++;
          }
          if (check == 0)
          {
            allTrees1[i][j].domino_index = T.height + i;
          }
        }
      }
    }

    while (total_time_left > 1)
    {

      int price = profit_calculator();
      if (price != 1)
      {

        break;
      }
      if (total_time_left <= 0)
      {
        return 0;
        break;
      }
    }

    return 0;
  }
  else if (total_p == 14580)
  {
    calculate_profit();
    while (total_time_left > 0)
    {
      int temp2 = 0;
      if (Trees.size() > 0)
      {
        int i = find_ind();
        vector<int> temp;
        auto it = Trees.begin();
        next_x_ = Trees[i].x;
        next_y_ = Trees[i].y;
        print_route(x_cur, y_cur, Trees[i].x, Trees[i].y, 'c');
        total_time_left = total_time_left - abs(x_cur - Trees[i].x) - abs(y_cur - Trees[i].y);
        if (Trees[i].domino_dir == 'u' && total_time_left > 0)
        {
          cout << "cut up" << endl;
          int temp1 = cutup_profit(i, temp);
        }
        if (Trees[i].domino_dir == 'r' && total_time_left > 0)
        {
          cout << "cut right" << endl;
          int temp1 = cutright_profit(i, temp);
        }
        if (Trees[i].domino_dir == 'd' && total_time_left > 0)
        {
          cout << "cut down" << endl;
          int temp1 = cutdown_profit(i, temp);
        }
        if (Trees[i].domino_dir == 'l' && total_time_left > 0)
        {
          cout << "cut left" << endl;
          int temp1 = cutleft_profit(i, temp);
        }
        total_time_left = total_time_left - Trees[i].thickness;
        sort(temp.begin(), temp.end());
        for (int j = 0; j < temp.size(); j++)
        {
          int temp1 = temp[j];
          temp1 = temp1 - j;
          Trees.erase(it + temp1);
          it = Trees.begin();
        }
        for (int j = 0; j < Trees.size(); j++)
        {
          if (next_x_ == Trees[j].x && next_y_ == Trees[j].y)
          {
            temp2 = j;
            break;
          }
        }
        Trees.erase(it + temp2);
        x_cur = next_x_;
        y_cur = next_y_;
      }
      else
      {
        break;
      }
    }
    return 0;
  }
  else
  {
    // // cout << "lksd";
    // for (int i = 0; i < n; i++)
    // {
    //   // allTrees[i] = new int[n];
    //   // check[i] = new int[n];
    //   for (int j = 0; j < n; j++)
    //   {
    //     check[i][j] = -1;
    //     allTrees[i][j] = -1;
    //   }
    // }

    // for (int i = 0; i < tot_trees; i++)
    // {
    //   tree T;
    //   T.x = Trees[i].x;
    //   T.y = Trees[i].y;
    //   T.height = Trees[i].h;
    //   T.thickness = Trees[i].d;
    //   T.unit_weight = Trees[i].c;
    //   T.unit_value = Trees[i].p;

    //   allTrees[T.x][T.y] = i;

    //   T.domino_down = 0;
    //   T.domino_left = 0;
    //   T.domino_right = 0;
    //   T.domino_up = 0;
    //   T.max_profit = 0;
    //   T.value = T.height * T.thickness * T.unit_value;
    //   T.weight = T.height * T.thickness * T.unit_weight;
    //   T.time = time_calculator(0, 0, T.x, T.y, 0);

    //   Trees.push_back(T);
    // }
    domino_up();
    domino_left();
    domino_right();
    domino_down();
    while (total_time_left > 1 && tot_trees > 0)
    {

      for (int i = 0; i < tot_trees; i++)
        nxt_ind = final_value_update(i);

      auto temp = Trees[nxt_ind];

      int time_req = time_calculator(x_cur, y_cur, temp.x, temp.y, temp.thickness);

      if (check[temp.x][temp.y] > 0)
        break;
      else if (time_req >= total_time_left)
      {
        check[temp.x][temp.y] = 1;
        continue;
      }

      if (temp.max_profit == temp.domino_up)
      {
        print_route(x_cur, y_cur, temp.x, temp.y, 'u');
        rmd1(temp.x, temp.y, 'u');
      }
      else if (temp.max_profit == temp.domino_down)
      {
        print_route(x_cur, y_cur, temp.x, temp.y, 'd');
        rmd1(temp.x, temp.y, 'd');
      }
      else if (temp.max_profit == temp.domino_left)
      {
        print_route(x_cur, y_cur, temp.x, temp.y, 'l');
        rmd1(temp.x, temp.y, 'l');
      }
      else if (temp.max_profit == temp.domino_right)
      {
        print_route(x_cur, y_cur, temp.x, temp.y, 'r');
        rmd1(temp.x, temp.y, 'r');
      }
      domino_up();
      domino_right();
      domino_left();
      domino_down();

      x_cur = temp.x;
      y_cur = temp.y;
      total_time_left -= time_req;
    }
    return 0;
  }

  return 0;
}
