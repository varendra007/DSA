
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct tree
{

  //### Provided as input

  int x_coord; //x coordinate
  int y_coord; //y coordinate
  int unit_value;
  int unit_weight;
  int height; // height of the tree
  int thickness;

  // ### To be calculated

  int value; // value = c*volume = p*h*d  now onwards value will contain value of domino if it's part of domino
  int domino_value;

  int weight;      // total weight of the tree
  float gain;      //total gain considering traveltime, cut_time and value value/time
  int time;        // time required to cut the tree plus required to navigate from prev coordinate
  char domino_dir; // L, R, U, D
  bool domino;     // if it's a part of domino or not

  int domino_up;
  int domino_left;
  int domino_right;
  int domino_down;
  int check;
};

vector<tree> Trees; // TODO we don't need this vector anymore will delete later if we didn't get any use of this
// int x = 0, y = 0;   // x and y of current coordinate where lumberjack is present

int x_cur = 0;
int y_cur = 0;

tree allTrees[10002][10002]; // will store tree at their cooudinates

int tree_count, grid_size, time_limit;
// int  k, n, t;
int tree_left;
int total_time_left, total_price = 0;

struct coordinate
{
  int x_coordinate;
  int y_coordinate;
};

int time_calculator(int x1, int y1, int x2, int y2, int d)
{
  return (abs(x2 - x1) + abs(y2 - y1) + d);
}

void printPath(int x2, int y2, char dir)
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

  // if (x2 == grid_size - 1) {
  //     cout << "cut left\n";
  // }
  // else {
  //     cout << "cut right\n";

  // }
  if (dir == 'u')
  {
    cout << "cut up\n";
  }
  else if (dir == 'r')
  {
    cout << "cut up\n";
  }
  else if (dir == 'l')
  {
    cout << "cut up\n";
  }
  else
  {
    cout << "cut down\n";
  }
}

int choose_opt(int ind1, int ind2, int t_r)
{
  tree T1 = Trees[ind1];
  tree T2 = Trees[ind2];

  int xii = T2.x_coord, yii = T2.y_coord, tii = T2.thickness;
  int xi = T1.x_coord, yi = T1.y_coord, ti = T1.thickness;

  int m1 = max({T1.domino_up, T1.domino_down, T1.domino_left, T1.domino_right});

  allTrees[xi][yi].domino_value += m1;

  int m2 = max({T2.domino_up, T2.domino_right, T2.domino_left, T2.domino_down});

  allTrees[xii][yii].domino_value += m2;

  int t1 = time_calculator(x_cur, y_cur, xi, yi, ti);
  int t2 = time_calculator(x_cur, y_cur, xii, yii, tii);

  if (ind1 < 0)
  {
    return ind2;
  }
  if (allTrees[xii][yii].check > 0)
    return ind1;

  if (allTrees[xi][yi].check > 0)
    return ind2;

  if (t2 <= t_r && (float)(m2) / (t2) > (float)(m1) / (t1))
    return ind2;

  return ind1;
}

void print_route(int x, int y, int x2, int y2)
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
}

void mark_all(pair<int, int> pos, char dir)
{
  int x = pos.first, y = pos.second, tar_ind, hei = allTrees[x][y].height, cur_x = x, cur_y = y;
  allTrees[x][y].check = 2;

  switch (dir)
  {

  case 'l':

    tar_ind = max(0, pos.first - hei + 1);
    while (x >= tar_ind)
    {

      if (allTrees[x][y].check != -1 && allTrees[x][y].check != 2)
      {

        tree T = allTrees[x][y];
        int c = T.unit_weight, h = T.height, t = T.thickness;

        tree T_ = allTrees[cur_x][cur_y];
        int c_ = T_.unit_weight, h_ = T_.height, t_ = T_.thickness;

        allTrees[x][y].check = 2;
        if (c * h * t < c_ * h_ * t_)
        {
          tar_ind = max(0, x - h + 1);
          cur_x = x;
        }
      }
      x--;
    }
    break;

  case 'r':
    tar_ind = min(pos.first + hei - 1, grid_size - 1);
    while (x <= tar_ind)
    {
      if (allTrees[x][y].check != -1 && allTrees[x][y].check != 2)
      {

        tree T = allTrees[x][y];
        int c = T.unit_weight, h = T.height, t = T.thickness;

        tree T_ = allTrees[cur_x][cur_y];
        int c_ = T_.unit_weight, h_ = T_.height, t_ = T_.thickness;

        allTrees[x][y].check = 2;
        if (c * h * t < c_ * h_ * t_)
        {
          tar_ind = min(grid_size - 1, x + h - 1);
          cur_x = x;
        }
        else
        {
          break;
        }
      }
      x++;
    }
    break;

  case 'u':
    tar_ind = min(pos.second + hei - 1, grid_size - 1);
    while (y <= tar_ind)
    {

      if (allTrees[x][y].check != -1 && allTrees[x][y].check != 2)
      {

        tree T = allTrees[x][y];
        int c = T.unit_weight, h = T.height, t = T.thickness;

        tree T_ = allTrees[cur_x][cur_y];
        int c_ = T_.unit_weight, h_ = T_.height, t_ = T_.thickness;

        allTrees[x][y].check = 2;
        if (c * h * t < c_ * h_ * t_)
        {
          tar_ind = min(grid_size - 1, y + h - 1);
          cur_y = y;
        }
        else
          break;
      }
      y++;
    }
    break;
  case 'd':
    tar_ind = max(pos.second - hei + 1, 0);
    while (y >= tar_ind)
    {

      if (allTrees[x][y].check != -1 && allTrees[x][y].check != 2)
      {

        tree T = allTrees[x][y];
        int c = T.unit_weight, h = T.height, t = T.thickness;

        tree T_ = allTrees[cur_x][cur_y];
        int c_ = T_.unit_weight, h_ = T_.height, t_ = T_.thickness;

        allTrees[x][y].check = 2;
        if (c * h * t < c_ * h_ * t_)
        {
          tar_ind = max(0, y - h + 1);
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

void calculate_Right()
{
  for (int y_index = 0; y_index < grid_size; y_index++)
  {
    for (int x_index = grid_size - 1; x_index >= 0; x_index--)
    {
      if (allTrees[x_index][y_index].check == -1)
      {
        continue;
      }

      if (allTrees[x_index][y_index].check == 2)
        continue;

      tree T_ = allTrees[x_index][y_index];
      int p_ = T_.unit_value, c_ = T_.unit_weight, d_ = T_.thickness, h_ = T_.height;

      allTrees[x_index][y_index].domino_right = T_.domino_right;

      int x = x_index, y = y_index;

      int right_dom_ind = min(x_index + h_, grid_size - 1);

      int cur_itr = x_index + 1;

      while (cur_itr < right_dom_ind)
      {

        if (allTrees[cur_itr][y_index].check != -1 && allTrees[cur_itr][y_index].check != 2)
        {

          tree variable = allTrees[cur_itr][y_index];
          int p = variable.unit_value, c = variable.unit_weight, d = variable.thickness, h = variable.height;

          tree _T = allTrees[x][y];

          int _p = _T.unit_value, _c = _T.unit_weight, _d = _T.thickness, _h = _T.height;

          if (_c * _d * _h < c * d * h)
            break;

          allTrees[x_index][y_index].domino_right += p * d * h;

          x = cur_itr;
          right_dom_ind = min(x + h, grid_size - 1);
        }
        cur_itr++;
      }
    }
  }

  cout << "right\n";
}

void calculate_Down()
{
  for (int y_index = 0; y_index < grid_size; y_index++)
  {
    for (int x_index = 0; x_index < grid_size; x_index++)
    {

      if (allTrees[x_index][y_index].check == -1)
      {
        continue;
      }

      if (allTrees[x_index][y_index].check == 2)
        continue;

      tree T_ = allTrees[x_index][y_index];
      int p_ = T_.unit_value, c_ = T_.unit_weight, d_ = T_.thickness, h_ = T_.height;

      allTrees[x_index][y_index].domino_down = T_.domino_down;

      int x = x_index, y = y_index;

      int down_dom_ind = max(y_index - h_, 0);

      int cur_itr = y_index - 1;

      while (cur_itr > down_dom_ind)
      {

        if (allTrees[x_index][cur_itr].check != -1 && allTrees[x_index][cur_itr].check != 2)
        {

          tree variable = allTrees[x_index][cur_itr];
          int p = variable.unit_value, c = variable.unit_weight, d = variable.thickness, h = variable.height;

          tree _T = allTrees[x][y];

          int _p = _T.unit_value, _c = _T.unit_weight, _d = _T.thickness, _h = _T.height;

          if (_c * _d * _h < c * d * h)
            break;

          allTrees[x_index][y_index].domino_down += p * d * h;

          y = cur_itr;
          down_dom_ind = max(y - h, 0);
        }
        cur_itr--;
      }
    }
  }
  cout << "down\n";
}

void calculate_Up()
{
  cout << "up\n";
  for (int y_index = grid_size - 1; y_index >= 0; y_index++)
  {
    for (int x_index = 0; x_index < grid_size; x_index++)
    {

      // cout << "up\n";
      if (allTrees[x_index][y_index].check == -1)
      {
        continue;
      }

      if (allTrees[x_index][y_index].check == 2)
        continue;

      tree T_ = allTrees[x_index][y_index];
      int p_ = T_.unit_value, c_ = T_.unit_weight, d_ = T_.thickness, h_ = T_.height;

      allTrees[x_index][y_index].domino_up = T_.domino_up;

      int x = x_index, y = y_index;

      int up_dom_ind = min(y_index + h_, grid_size - 1);

      int cur_itr = y_index + 1;

      while (cur_itr < up_dom_ind)
      {

        if (allTrees[x_index][cur_itr].check != -1 && allTrees[x_index][cur_itr].check != 2)
        {

          tree variable = allTrees[x_index][cur_itr];
          int p = variable.unit_value, c = variable.unit_weight, d = variable.thickness, h = variable.height;

          tree _T = allTrees[x][y];

          int _p = _T.unit_value, _c = _T.unit_weight, _d = _T.thickness, _h = _T.height;

          if (_c * _d * _h < c * d * h)
            break;

          allTrees[x_index][y_index].domino_up += p * d * h;

          y = cur_itr;
          up_dom_ind = min(y + h, grid_size - 1);
          cout << "ladf";
        }
        cout << "la";
        cur_itr++;
      }
    }
  }

  cout << "up\n";
}

void calculate_Left()
{
  for (int y_index = 0; y_index < grid_size; y_index++)
  {
    for (int x_index = 0; x_index < grid_size; x_index++)
    {
      if (allTrees[x_index][y_index].check == -1)
      {
        continue;
      }

      if (allTrees[x_index][y_index].check == 2)
        continue;

      tree T_ = allTrees[x_index][y_index];
      int p_ = T_.unit_value, c_ = T_.unit_weight, d_ = T_.thickness, h_ = T_.height;

      allTrees[x_index][y_index].domino_left = T_.domino_left;

      int x = x_index, y = y_index;

      int left_dom_ind = max(x_index - h_, 0);

      int cur_itr = x_index - 1;

      while (cur_itr > left_dom_ind)
      {

        if (allTrees[cur_itr][y_index].check != -1 && allTrees[cur_itr][y_index].check != 2)
        {

          tree variable = allTrees[cur_itr][y_index];
          int p = variable.unit_value, c = variable.unit_weight, d = variable.thickness, h = variable.height;

          tree _T = allTrees[x][y];

          int _p = _T.unit_value, _c = _T.unit_weight, _d = _T.thickness, _h = _T.height;

          if (_c * _d * _h < c * d * h)
            break;

          allTrees[x_index][y_index].domino_left += p * d * h;

          x = cur_itr;
          left_dom_ind = max(x - h, 0);
        }
        cur_itr--;
      }
    }
  }

  cout << "left\n";
}

//

int profit_calculator()
{

  cout << "532\n";
  vector<tree> left_trees;
  tree_left = 0;
  left_trees.clear();

  calculate_Up();
  calculate_Left();
  calculate_Right();
  calculate_Down();

  cout << "542\n";
  // Todo chidaksh way of searching tree
  for (int i = 0; i < grid_size; i++)
  {
    for (int j = 0; j < grid_size; j++)
    {
      if (allTrees[i][j].x_coord == i && allTrees[i][j].y_coord == j)
      {

        allTrees[i][j].time = time_calculator(x_cur, y_cur, i, j, allTrees[i][j].thickness);
        allTrees[i][j].gain = max({allTrees[i][j].domino_up, allTrees[i][j].domino_down, allTrees[i][j].domino_right, allTrees[i][j].domino_left}) / allTrees[i][j].time;
        tree_left++;
        // if we can cut tree in given time than push it in vector
        if (allTrees[i][j].time <= total_time_left)
        {
          left_trees.push_back(allTrees[i][j]);
        }
      }
    }
  }
  cout << "562\n";
  // we can't cut any tree
  if (left_trees.empty())
  {
    cout << "566\n";
    return -1;
  }
  if (total_time_left <= 0)
  {
    cout << "571\n";
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
  total_price += left_trees[tree_index].value;
  tree_left -= 1; //Todo later we'll consider domino to

  //Todo remove tree and domino and printing path and then change current coordinate of lumber
  int x_coord = left_trees[tree_index].x_coord;
  int y_coord = left_trees[tree_index].y_coord;

  tree temp = allTrees[x_coord][y_coord];

  int domino_value = max({temp.domino_up, temp.domino_down, temp.domino_left, temp.domino_right});

  // rmd(x_coord, y_coord); // removed domino
  char dir = 'r';
  // if (left_trees[tree_index].domino)
  // {
  //   dir = left_trees[tree_index].domino_dir;
  //   //!!!!! rmd2(x_coord, y_coord, left_trees[tree_index].domino_dir);
  // }

  // if(allTrees[x_coord][y_coord].domino_value)

  if (domino_value == temp.domino_up)
  {
    cout << "up\n";
    printPath(x_coord, y_coord, 'u'); // printed path
    mark_all(make_pair(x_coord, y_coord), 'u');
  }
  else if (domino_value == temp.domino_down)
  {
    cout << "down\n";
    printPath(x_coord, y_coord, 'd'); // printed path
    mark_all(make_pair(x_coord, y_coord), 'd');
  }
  else if (domino_value == temp.domino_left)
  {
    cout << "left";
    printPath(x_coord, y_coord, 'l'); // printed path
    mark_all(make_pair(x_coord, y_coord), 'l');
  }
  else if (domino_value == temp.domino_right)
  {
    cout << "right" << endl;
    printPath(x_coord, y_coord, 'r'); // printed path
    mark_all(make_pair(x_coord, y_coord), 'r');
  }
  cout << "634\n";
  total_time_left -= left_trees[tree_index].time;

  // removed tree
  // allTrees[x_coord][y_coord].x_coord = -1;
  // allTrees[x_coord][y_coord].y_coord = -1;
  x_cur = x_coord, y_cur = y_coord;

  return 1;
}

int main()
{

  cin >> time_limit >> grid_size >> tree_count;
  tree_left = tree_count;
  total_time_left = time_limit;

  const int g_size = grid_size;

  //    allTrees = new tree [g_size][g_size];

  // allTrees = new tree *[grid_size];

  tree T1;

  for (int i = 0; i < 10002; i++)
  {
    // allTrees[i] = new tree[grid_size];
    for (int j = 0; j < 10002; j++)
    {
      // T1.x_coord = -1;
      // T1.y_coord = -1;

      // allTrees[i][j] = T1;
      allTrees[i][j].check = -1;
      allTrees[i][j].x_coord = -1;
      allTrees[i][j].y_coord = -1;
    }
  }

  // taking input
  for (int i = 0; i < tree_count; i++)
  {
    tree T;
    cin >> T.x_coord >> T.y_coord >> T.height >> T.thickness >> T.unit_weight >> T.unit_value;

    T.weight = T.unit_weight * T.height * T.thickness;
    T.value = T.unit_value * T.height * T.thickness;

    T.domino = false;
    T.domino_value = T.value;
    T.check = 0;
    T.domino_down = T.value;
    T.domino_up = T.value;
    T.domino_right = T.value;
    T.domino_left = T.value;
    Trees.push_back(T);

    // we will store info about tree at their coordinate index
    allTrees[T.x_coord][T.y_coord] = T;
  }

  // while (total_time_left > 1)
  // {
  //   if (tree_left <= 0 || total_time_left < 1)
  //   {
  //     // return 0;
  //     break;
  //   }
  //   cout << "704\n";
  //   int price = profit_calculator();
  //   cout << "705\n";
  //   // if (price != 1)
  //   // {

  //   //   break;
  //   // }
  //   if (total_time_left <= 0)
  //   {
  //     // return 0;
  //     break;
  //   }
  // }

  // while (total_time_left--)
  // {
  //   // cout << "\n385 " << total_time_left << endl;
  //   // x = 0;
  //   if (x > 0)
  //   {
  //     cout << "move left\n";
  //     x--;
  //   }
  //   else
  //   {
  //     total_time_left++;
  //     while (++x < grid_size - 1 && total_time_left--)
  //     {
  //       cout << "move right\n";

  //       // total_time_left--;
  //       if (total_time_left <= 0)
  //       {
  //         break;
  //       }
  //     }
  //   }
  //   if (total_time_left <= 0)
  //   {
  //     break;
  //   }
  // }

  calculate_Up();
  calculate_Left();
  calculate_Right();
  calculate_Down();

  int target_index = 0;

  while (total_time_left > 1)
  {

    for (int i = 0; i <= tree_count; i++)
      target_index = choose_opt(target_index, i, total_time_left);
    // assert(target_index <= number_of_trees && target_index > 0);

    auto temp = Trees[target_index];

    int x_needed = abs(x_cur - temp.x_coord), y_needed = abs(y_cur - temp.y_coord);
    int time_required_for_this_tree = x_needed + y_needed + temp.thickness;

    if (allTrees[temp.x_coord][temp.y_coord].check > 0)
      break;
    else if (time_required_for_this_tree >= total_time_left)
    {
      allTrees[temp.x_coord][temp.y_coord].check = 1;
      continue;
    }

    int max_data = max({temp.domino_left, temp.domino_down, temp.domino_right, temp.domino_up});

    if (max_data == temp.domino_up)
    {
      print_route(x_cur, y_cur, temp.x_coord, temp.y_coord);
      cout << "cut up\n";
      mark_all(make_pair(temp.x_coord, temp.y_coord), 'u');
    }
    else if (max_data == temp.domino_down)
    {
      print_route(x_cur, y_cur, temp.x_coord, temp.y_coord);
      cout << "cut down\n";
      mark_all(make_pair(temp.x_coord, temp.y_coord), 'd');
    }
    else if (max_data == temp.domino_left)
    {
      print_route(x_cur, y_cur, temp.x_coord, temp.y_coord);
      cout << "cut left\n";
      mark_all(make_pair(temp.x_coord, temp.y_coord), 'l');
    }
    else if (max_data == temp.domino_right)
    {
      print_route(x_cur, y_cur, temp.x_coord, temp.y_coord);
      cout << "cut right\n";
      mark_all(make_pair(temp.x_coord, temp.y_coord), 'r');
    }
    // calculate_Up();
    // calculate_Right();
    // calculate_Left();
    // calculate_Down();

    // position = make_pair(temp.x, temp.y);
    x_cur = temp.x_coord;
    y_cur = temp.y_coord;
    total_time_left -= time_required_for_this_tree;
  }
  return 0;
}
