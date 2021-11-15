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
};

// to store the index of tree that is at given coordinates on the grid
int **allTrees, grid_size;
int **check;
int nxt_ind = 0;
int total_time_left, tot_trees;

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

    Trees.push_back(T);
  }

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