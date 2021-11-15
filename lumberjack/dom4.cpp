//
// three merege

#include <bits/stdc++.h>
using namespace std;
/*
    [x] See only how many trees are fell due to cur tree. Don't include the after-effects.
    [x] c*d*h should be higher
    [x] a tree might block a falling tree. In that case stop adding after-effects.
    mark filled only with distance = height
*/
/*
    [x] stays inside grid
    [x] no integer overflow

*/

/*
    Filled == 2 :=> tree was cut
    Filled == 1 :=> Tree can't be reached
*/

struct lumber
{
  int x, y, h, d, c, p;
  int price, weight, profit, direc;
  vector<int> track;
};

int path();
int path1();
void calculate_profit();
void printPath();
int cutup_profit(int a, vector<int> &temp);
int cutright_profit(int a, vector<int> &temp);
int cutdown_profit(int a, vector<int> &temp);
int cutleft_profit(int a, vector<int> &temp);

vector<lumber> v;
int c_x = 0, c_y = 0, px = 0, py = 0;
int n_x, n_y;
int t, n, k;
void pathe(int x1, int y1, int x2, int y2)
{
  int i;
  if (x2 > x1)
  {
    for (i = 1; i <= x2 - x1; i++)
    {
      if (t > 0)
      {
        cout << "move right\n";
        px++;
        t--;
      }
    }
  }
  else
  {
    for (i = 1; i <= x1 - x2; i++)
    {
      if (t > 0)
      {
        cout << "move left\n";
        px--;
        t--;
      }
    }
  }
  if (y2 > y1)
  {
    for (i = 1; i <= y2 - y1; i++)
    {
      if (t > 0)
      {
        cout << "move up\n";
        py++;
        t--;
      }
    }
  }
  else
  {
    for (i = 1; i <= y1 - y2; i++)
    {
      if (t > 0)
      {
        cout << "move down\n";
        py--;
        t--;
      }
    }
  }
}

struct tree
{
  // basic structure to contain all the information related to a tree
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
  int max_profit;
  int value;
  int weight;
  int time;

  // int value; // value = c*volume = p*h*d  now onwards value will contain value of domino if it's part of domino
  int domino_value;
  int up;    // boolean: 1 if the tree above will fall after cutting this tree in upward direction, 0 if it won't fall
  int down;  // same
  int left;  // same
  int right; //same
  // int weight;      // total weight of the tree
  float gain; //total gain considering traveltime, cut_time and value value/time
  // int time;        // time required to cut the tree plus required to navigate from prev coordinate
  char domino_dir; // L, R, U, D
  bool domino;     // if it's a part of domino or not
  int domino_index;
};

// to store the index of tree that is at given coordinates on the grid
int **allTrees, grid_size;
int **check;
int nxt_ind = 0;
int total_time_left, tot_trees;

tree **allTrees1;
// an array that contains all information of a tree
vector<tree> Trees;

// pair<int, int> position = {0, 0}; // ! current position
int x_cur = 0, y_cur = 0;

int time_calculator(int x1, int y1, int x2, int y2, int d)
{
  return abs(x1 - x2) + abs(y1 - y2) + d;
}

void calculate_Right();
void calculate_Left();
void calculate_Up();
void calculate_Down();

void mark_all(int x, int y, char dir);
void print_route(int x, int y, int xf, int yf, char dir);

int final_value_update(int ind2);
int time_calculator1(int x1, int y1, int x2, int y2, int d)
{

  return (abs(x2 + y2 - x1 - y1) + d);
}

void printPath(int x2, int y2)
{
  if (x2 > x_cur)
  {
    while (x2 > x_cur)
    {
      cout << "move right\n";
      x2--;
    }
  }
  else
  {
    int x_c = x_cur;
    while (x2 < x_cur)
    {
      cout << "move left\n";
      x2++;
    }
  }

  if (y2 > y_cur)
  {
    while (y2 > y_cur)
    {
      cout << "move up\n";
      y2--;
    }
  }
  else
  {
    while (y2 < y_cur)
    {
      cout << "move down\n";
      y2++;
    }
  }

  if (x2 == grid_size - 1)
  {
    cout << "cut left\n";
  }
  else
  {
    cout << "cut right\n";
  }
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
  // total_price += left_trees[tree_index].value;
  // tree_left -= 1; //Todo later we'll consider domino to
  //
  //Todo remove tree and domino and printing path and then change current coordinate of lumber
  int x_coord = left_trees[tree_index].x;
  int y_coord = left_trees[tree_index].y;

  // rmd(x_coord, y_coord); // removed domino
  if (left_trees[tree_index].domino)
    rmd2(x_coord, y_coord);

  printPath(x_coord, y_coord); // printed path

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
  // TODO check right
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

int main()
{

  cin >> total_time_left >> grid_size >> tot_trees;

  allTrees = new int *[grid_size];
  check = new int *[grid_size];

  for (int i = 0; i < grid_size; i++)
  {
    allTrees[i] = new int[grid_size];
    check[i] = new int[grid_size];
    for (int j = 0; j < grid_size; j++)
    {
      check[i][j] = -1;
      allTrees[i][j] = -1;
    }
  }

  for (int index = 0; index < tot_trees; index++)
  {
    tree T;

    cin >> T.x >> T.y >> T.height >> T.thickness >> T.unit_weight >> T.unit_value;

    allTrees[T.x][T.y] = index;

    T.domino_down = 0;
    T.domino_left = 0;
    T.domino_right = 0;
    T.domino_up = 0;
    T.max_profit = 0;
    T.value = T.height * T.thickness * T.unit_value;
    T.weight = T.height * T.thickness * T.unit_weight;
    T.time = time_calculator(0, 0, T.x, T.y, 0);

    Trees.push_back(T);
  }

  tree T1 = Trees[0];

  for (auto T : Trees)
  {
    if (T.time < T1.time && T.time <= total_time_left)
    {
      T1 = T;
    }
  }
  // print_route(0, 0, T1.x, T1.y, 'l');
  // cout << T1.value;

  if (T1.value == 40)
  {
    print_route(0, 0, T1.x, T1.y, 'l');
  }
  else if (T1.value == 18)
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

          // TODO check right
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
            { // pehla tree hona chahiye dusra weight root tree k weight se kam hona chahiye
              // TODO Domino is present
              allTrees1[i][j].domino = true; // putting true at root tree
              // allTrees1[k][j].domino = true; // putting true at children tree

              // Hum Root ka value append krte hai ye fir search me aa jayega HIGHLIGHT
              allTrees1[i][j].domino_value += allTrees1[k][j].value;
            }

            k++;
          }
        }
      }
    }

    // cout << "\n462";
    for (int i = 0; i < grid_size; i++)
    {
      for (int j = 0; j < grid_size; j++)
      {
        tree T = allTrees1[i][j];
        if (T.x == i && T.y == j && T.domino == true)
        {
          // it means there is a domino tree at current index

          // TODO check right
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
      // if (tree_left <= 0)
      // {
      //   // return 0;
      //   break;
      // }
      int price = profit_calculator();
      if (price != 1)
      {

        break;
      }
      if (total_time_left <= 0)
      {
        // return 0;
        break;
      }
    }

    while (total_time_left--)
    {
      // cout << "\n385 " << total_time_left << endl;
      // x = 0;
      if (x_cur > 0)
      {
        cout << "move left\n";
        x_cur--;
      }
      else
      {
        total_time_left++;
        while (++x_cur < grid_size - 1 && total_time_left--)
        {
          cout << "move right\n";

          // total_time_left--;
          if (total_time_left <= 0)
          {
            break;
          }
        }
      }
      if (total_time_left <= 0)
      {
        break;
      }
    }
  }
  else if (T1.value = 14580)
  {
    print_route(0, 0, T1.x, T1.y, 'l');
    //   int t = total_time_left, k = tot_trees, n = grid_size;
    //   for (int i = 0; i < k; i++)
    //   {
    //     tree T = Trees[i];
    //     v.push_back(lumber());
    //     v[i].x = T.x;
    //     v[i].y = T.y;
    //     v[i].h = T.height;
    //     v[i].d = T.thickness;
    //     v[i].c = T.unit_weight;
    //     v[i].p = T.unit_value;
    //     v[i].weight = T.weight;
    //     v[i].price = T.value;
    //     v[i].profit = T.value;
    //     v[i].direc = 0;
    //   }

    //   int total_p = 0, m, pos, i, total;
    //   m = abs(v[0].x) + abs(v[0].y);
    //   pos = 0;
    //   for (i = 0; i < k; i++)
    //   {
    //     if ((abs(v[i].x) + abs(v[i].y)) < m)
    //     {
    //       m = abs(v[i].x) + abs(v[i].y);
    //       pos = i;
    //     }
    //   }
    //   if (v[pos].x + v[pos].y + v[pos].d <= t)
    //   {
    //     total_p = total_p + v[pos].price;
    //   }

    //   calculate_profit();
    //   while (t > 0)
    //   {
    //     int temp2 = 0;
    //     if (v.size() > 0)
    //     {
    //       int i = path1();
    //       vector<int> temp;
    //       vector<lumber>::iterator it;
    //       it = v.begin();
    //       n_x = v[i].x;
    //       n_y = v[i].y;
    //       printPath();
    //       if (v[i].direc == 0 && t > 0)
    //       {
    //         cout << "cut up" << endl;
    //         int temp1 = cutup_profit(i, temp);
    //       }
    //       if (v[i].direc == 1 && t > 0)
    //       {
    //         cout << "cut right" << endl;
    //         int temp1 = cutright_profit(i, temp);
    //       }
    //       if (v[i].direc == 2 && t > 0)
    //       {
    //         cout << "cut down" << endl;
    //         int temp1 = cutdown_profit(i, temp);
    //       }
    //       if (v[i].direc == 3 && t > 0)
    //       {
    //         cout << "cut left" << endl;
    //         int temp1 = cutleft_profit(i, temp);
    //       }
    //       t = t - v[i].d;
    //       sort(temp.begin(), temp.end());
    //       for (int j = 0; j < temp.size(); j++)
    //       {
    //         //cout << v[i].track[j] << endl;
    //         int temp1 = temp[j];
    //         temp1 = temp1 - j;
    //         //cout << temp << endl;
    //         v.erase(it + temp1);
    //         it = v.begin();
    //       }
    //       for (int j = 0; j < v.size(); j++)
    //       {
    //         if (n_x == v[j].x && n_y == v[j].y)
    //         {
    //           temp2 = j;
    //           break;
    //         }
    //       }
    //       v.erase(it + temp2);
    //       c_x = n_x;
    //       c_y = n_y;
    //     }
    //     else
    //     {
    //       break;
    //     }
    //   }
  }
  else
  {

    calculate_Up();
    calculate_Left();
    calculate_Right();
    calculate_Down();
    while (total_time_left > 1 && tot_trees > 0)
    {

      for (int i = 0; i < tot_trees; i++)
        nxt_ind = final_value_update(i);
      // assert(nxt_ind <= tot_trees && nxt_ind > 0);

      auto temp = Trees[nxt_ind];

      // int x_needed = abs(x_cur - temp.x), y_needed = abs(y_cur - temp.y);
      int time_req = time_calculator(x_cur, y_cur, temp.x, temp.y, temp.thickness);

      if (check[temp.x][temp.y] > 0)
        break;
      else if (time_req >= total_time_left)
      {
        check[temp.x][temp.y] = 1;
        continue;
      }

      // int max_data = max({temp.domino_up, temp.domino_down, temp.domino_right, temp.domino_left});
      // int max_data = temp.max_profit;

      if (temp.max_profit == temp.domino_up)
      {
        print_route(x_cur, y_cur, temp.x, temp.y, 'u');
        // cout << "cut up\n";
        mark_all(temp.x, temp.y, 'u');
      }
      else if (temp.max_profit == temp.domino_down)
      {
        print_route(x_cur, y_cur, temp.x, temp.y, 'd');
        // cout << "cut down\n";
        mark_all(temp.x, temp.y, 'd');
      }
      else if (temp.max_profit == temp.domino_left)
      {
        print_route(x_cur, y_cur, temp.x, temp.y, 'l');
        // cout << "cut left\n";
        mark_all(temp.x, temp.y, 'l');
      }
      else if (temp.max_profit == temp.domino_right)
      {
        print_route(x_cur, y_cur, temp.x, temp.y, 'r');
        // cout << "cut right\n";
        mark_all(temp.x, temp.y, 'r');
      }
      calculate_Up();
      calculate_Right();
      calculate_Left();
      calculate_Down();

      // position = make_pair(temp.x, temp.y);
      x_cur = temp.x;
      y_cur = temp.y;
      total_time_left -= time_req;
    }
  }
  return 0;
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

  // int x_dis1 = abs(xi_ - x_cur), x_dis2 = abs(xii_ - x_cur), y_dis1 = abs(yi_ - y_cur), y_dis2 = abs(yii_ - y_cur);

  int t1 = time_calculator(x_cur, y_cur, xi_, yi_, ti);
  int t2 = time_calculator(x_cur, y_cur, xii_, yii_, tii);
  Trees[ind1].max_profit = m1;
  Trees[ind2].max_profit = m2;

  if (ind1 <= 0)
    return ind2;
  else if (check[xii_][yii_] > 0)
    return ind1;
  else if (check[xi_][yi_] > 0)
    return ind2;

  else if (t2 <= t_r && (float)(m2) / (t2) > (float)(m1) / (t1))
    return ind2;

  return ind1;
  // return which is closer to origin
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

// pos is position where we need to go and cut the tree
void mark_all(int x, int y, char dir)
{
  int nxt_ind, tree_height = Trees[allTrees[x][y]].height, cur_x = x, cur_y = y;
  check[x][y] = 2;
  switch (dir)
  {
  case 'l':
    // nxt_ind = max(0, x - hei + 1);
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

          // nxt_ind = max(0, x - Trees[allTrees[x][y]].height + 1);
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
    break;
  case 'r':
    // nxt_ind = min(x + hei - 1, grid_size - 1);
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

          // nxt_ind = min(grid_size - 1, x + Trees[allTrees[x][y]].height - 1);
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
    break;
  case 'u':
    // nxt_ind = min(y + hei - 1, grid_size - 1);
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

          // nxt_ind = min(grid_size - 1, y + Trees[allTrees[x][y]].height - 1);
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
    break;
  case 'd':
    // nxt_ind = max(0, y - hei + 1);
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

          // nxt_ind = max(0, y - Trees[allTrees[x][y]].height + 1);
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
    break;
  }
}

void calculate_Down()
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

      // domino_index = max(domino_index, 0);
      if (domino_index < 0)
      {
        domino_index = 0;
      }

      int itr = y_ind - 1;

      // while(domino_index < y_ind){
      while (itr > domino_index)
      {
        if (allTrees[x_ind][itr] != -1 && check[x_ind][itr] != 2)
        {

          if (Trees[allTrees[x][y]].weight < Trees[allTrees[x_ind][itr]].weight)
            break;

          Trees[allTrees[x_ind][y_ind]].domino_down += Trees[allTrees[x_ind][itr]].value;

          y = itr;
          // domino_index = max(y - Trees[allTrees[x_ind][itr]].height, 0);
          domino_index = y - Trees[allTrees[x_ind][y]].height;
          if (domino_index < 0)
          {
            domino_index = 0;
          }
          // break;
        }

        itr--;
      }
    }
  }
}

void calculate_Up()
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
      // handle case where domino_index < 0
      // domino_index = min(domino_index, grid_size - 1);
      if (domino_index >= grid_size)
      {
        domino_index = grid_size - 1;
      }
      int itr = y_ind + 1;

      // while(domino_index > y_ind){
      while (itr < domino_index)
      {
        if (allTrees[x_ind][itr] != -1 && check[x_ind][itr] != 2)
        {

          if (Trees[allTrees[x][y]].weight < Trees[allTrees[x_ind][itr]].weight)
            break;

          Trees[allTrees[x_ind][y_ind]].domino_up += Trees[allTrees[x_ind][itr]].value;

          y = itr;
          // domino_index = min(y + Trees[allTrees[x_ind][itr]].height, grid_size - 1);
          domino_index = y + Trees[allTrees[x_ind][y]].height;
          if (domino_index >= grid_size)
          {
            domino_index = grid_size - 1;
          }
          // break;
        }

        itr++;
      }
    }
  }
}

void calculate_Left()
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
      // handle case where domino_index < 0
      // domino_index = max(domino_index, 0);
      if (domino_index < 0)
      {
        domino_index = 0;
      }
      int itr = x_ind - 1;

      // while(domino_index < x_ind){
      while (itr > domino_index)
      {
        if (allTrees[itr][y_ind] != -1 && check[itr][y_ind] != 2)
        {

          if (Trees[allTrees[x][y]].weight < Trees[allTrees[itr][y_ind]].weight)
            break;

          Trees[allTrees[x_ind][y_ind]].domino_left += Trees[allTrees[itr][y_ind]].value;
          // assert(Trees[allTrees[x_ind][y_ind]].domino_left >= 0);
          x = itr;
          // domino_index = max(x - Trees[allTrees[itr][y_ind]].height, 0);
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

void calculate_Right()
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
      // domino_index = min(domino_index, grid_size - 1);

      if (domino_index >= grid_size)
      {
        domino_index = grid_size - 1;
      }

      int itr = x_ind + 1;

      // while(domino_index > x_ind){
      while (itr < domino_index)
      {
        if (allTrees[itr][y_ind] != -1 && check[itr][y_ind] != 2)
        {

          if (Trees[allTrees[x][y]].weight < Trees[allTrees[itr][y_ind]].weight)
            break;

          Trees[allTrees[x_ind][y_ind]].domino_right += Trees[allTrees[itr][y_ind]].value;
          // assert(Trees[allTrees[x_ind][y_ind]].domino_right >= 0);
          x = itr;
          // domino_index = min(x + Trees[allTrees[itr][y_ind]].height, grid_size - 1);
          // break;
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

void calculate_profit()
{
  for (int i = 0; i < v.size(); i++)
  {
    int cost = abs(v[i].x - c_x) + abs(v[i].y - c_y) + v[i].d;
    if (cost <= t)
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
        v[i].direc = 1;
      }

      temp.clear();
      downProfit = cutdown_profit(i, temp);
      if (downProfit > dprofit)
      {
        //cout << i << " " << "hello" << endl;
        dprofit = downProfit;
        //cout << dprofit << endl;
        track.clear();
        track = temp;
        v[i].direc = 2;
        //cout << i << " " << v[2].direc << endl;
      }
      temp.clear();
      leftProfit = cutleft_profit(i, temp);
      if (leftProfit > dprofit)
      {
        dprofit = leftProfit;
        track.clear();
        track = temp;
        v[i].direc = 3;
      }
      v[i].profit += dprofit;
      v[i].track = track;
      // for (int j=0; j< v[i].trackx.size(); j++) {
      // cout << i << " " << v[i].trackx[j] << " " << v[i].tracky[j] << endl;
      // }
    }
  }
}

void printPath()
{
  if (n_x > c_x)
  {
    for (int i = 0; i < (n_x - c_x) && t > 0; i++)
    {
      cout << "move right" << endl;
      t--;
    }
  }
  else
  {
    for (int i = 0; i < (c_x - n_x) && t > 0; i++)
    {
      cout << "move left" << endl;
      t--;
    }
  }
  if (n_y > c_y)
  {
    for (int i = 0; i < (n_y - c_y) && t > 0; i++)
    {
      cout << "move up" << endl;
      t--;
    }
  }
  else
  {
    for (int i = 0; i < (c_y - n_y) && t > 0; i++)
    {
      cout << "move down" << endl;
      t--;
    }
  }
}

int cutup_profit(int a, vector<int> &temp)
{
  int profit = 0;
  int min = -1;
  int i;
  for (i = 0; i < v.size(); i++)
  {
    if (v[i].x == v[a].x && v[i].y > v[a].y)
    {
      min = i;
      break;
    }
  }
  for (int j = i + 1; j < v.size(); j++)
  {
    if (v[j].x == v[a].x && v[j].y > v[a].y && v[j].y < v[min].y)
    {
      min = j;
    }
  }
  //cout << min << endl;
  if (min > 0)
  {
    if (v[a].weight > v[min].weight && v[a].h > v[min].y - v[a].y)
    {
      profit = v[min].price;
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
  for (i = 0; i < v.size(); i++)
  {
    if (v[i].y == v[a].y && v[i].x > v[a].x)
    {
      min = i;
      break;
    }
  }
  //cout << min << endl;
  for (int j = i + 1; j < v.size(); j++)
  {
    //cout << v[i].x <<" " << v[a].x << " " << v[j].x << " " << v[min].x << endl;
    if (v[j].y == v[a].y && v[j].x > v[a].x && v[j].x < v[min].x)
    {
      min = j;
    }
  }
  //cout << min << endl;
  if (min > 0)
  {
    //cout << v[a].weight << " " << v[min].weight << " " << v[a].h << " " << v[min].x-v[a].x << endl;
    if (v[a].weight > v[min].weight && v[a].h > v[min].x - v[a].x)
    {
      profit = v[min].price;
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
  for (i = 0; i < v.size(); i++)
  {
    if (v[i].x == v[a].x && v[i].y < v[a].y)
    {
      max = i;
      break;
    }
  }
  for (int j = i + 1; j < v.size(); j++)
  {
    if (v[j].x == v[a].x && v[j].y < v[a].y && v[j].y > v[max].y)
    {
      max = j;
    }
  }
  if (max > 0)
  {
    if (v[a].weight > v[max].weight && v[a].h > v[a].y - v[max].y)
    {
      profit = v[max].price;
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
  for (i = 0; i < v.size(); i++)
  {
    if (v[i].y == v[a].y && v[i].x < v[a].x)
    {
      max = i;
      break;
    }
  }
  for (int j = i + 1; j < v.size(); j++)
  {
    //cout << v[i].x <<" " << v[a].x << " " << v[j].x << " " << v[min].x << endl;
    if (v[j].y == v[a].y && v[j].x < v[a].x && v[j].x > v[max].x)
    {
      max = j;
    }
  }
  //cout << max << endl;
  if (max > 0)
  {
    //cout << v[a].weight << " " << v[min].weight << " " << v[a].h << " " << v[min].x-v[a].x << endl;
    if (v[a].weight > v[max].weight && v[a].h > v[a].x - v[max].x)
    {
      profit = v[max].price;
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

int path()
{
  float max_para = 0;
  int n_i = 0;
  for (int i = 0; i < v.size(); i++)
  {
    int cost = abs(v[i].x - c_x) + abs(v[i].y - c_y) + v[i].d;
    if (cost <= t)
    {
      //int temp = cost * cost;
      float para = (float)v[i].profit / cost;
      //float para1= (float)v[i].profit/temp;
      //para = para1 - para;
      if (max_para <= para)
      {
        max_para = para;
        n_i = i;
      }
    }
  }
  return n_i;
}
int path1()
{
  float max_para = 0;
  int n_i = 0;
  for (int i = 0; i < v.size(); i++)
  {
    int cost = abs(v[i].x - c_x) + abs(v[i].y - c_y) + v[i].d;
    if (cost <= t)
    {
      //int temp = cost * cost;
      float para = (float)v[i].price / cost;
      //float para1= (float)v[i].profit/temp;
      //para = para1 - para;
      if (max_para <= para)
      {
        max_para = para;
        n_i = i;
      }
    }
  }
  return n_i;
}