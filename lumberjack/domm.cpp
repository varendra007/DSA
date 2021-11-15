#include <bits/stdc++.h>
using namespace std;

// void check_udlr(struct tree *T); // check_up_down_left_right()
// void calculate_gain(struct tree *T);

vector<tree1> Trees; // TODO we don't need this vector anymore will delete later if we didn't get any use of this
int x = 0, y = 0;    // x and y of current coordinate where lumberjack is present

tree1 **allTrees; // will store tree at their cooudinates

int tree_count, grid_size, time_limit;
// int  k, n, t;
int tree_left;
int total_time_left, total_price = 0;

struct tree1
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
  int up;          // boolean: 1 if the tree above will fall after cutting this tree in upward direction, 0 if it won't fall
  int down;        // same
  int left;        // same
  int right;       //same
  int weight;      // total weight of the tree
  float gain;      //total gain considering traveltime, cut_time and value value/time
  int time;        // time required to cut the tree plus required to navigate from prev coordinate
  char domino_dir; // L, R, U, D
  bool domino;     // if it's a part of domino or not
  int domino_index;
};

struct coordinate
{
  int x_coordinate;
  int y_coordinate;
};

int time_calculator(int x1, int y1, int x2, int y2, int d)
{

  return (abs(x2 + y2 - x1 - y1) + d);
}

void printPath(int x2, int y2)
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

  if (x2 == grid_size - 1)
  {
    cout << "cut left\n";
  }
  else
  {
    cout << "cut right\n";
  }
}
/* x2 and y2 are coordinates of tree which is just cutted by lumber */
int rmd(int x2, int y2)
{

  int check = 0;
  for (int i = 0; i <= allTrees[x2][y2].height; i++)
  {
    if (i + x2 >= grid_size)
    {
      break;
    }
    else
    {
      if (allTrees[i + x2][y2].x_coord == i + x2 && allTrees[x2][y2].weight > allTrees[i + x2][y2].weight)
      {
        check++;
        break;
      }
    }
  }
  if (check == 0)
  {
    return 0;
  }
  for (int i = x2 + 1; i < grid_size; i++)
  {
    if (i >= grid_size)
    {
      break;
    }
    else
    {
      if (allTrees[i][y2].x_coord == i && allTrees[i][y2].y_coord == y2)
      {
        allTrees[i][y2].x_coord = -1;
        allTrees[i][y2].y_coord = -1;
      }
    }
  }
  return 0;
}

void rmd2(int x1, int y1)
{
  for (int i = 0; i < grid_size; i++)
  {
    if (allTrees[i][y1].x_coord == i && allTrees[i][y1].y_coord == y1)
    {
      allTrees[i][y1].x_coord = -1;
      allTrees[i][y1].y_coord = -1;
    }
  }
}

int profit_calculator()
{
  vector<tree1> left_trees;
  tree_left = 0;
  left_trees.clear();
  for (int i = 0; i < grid_size; i++)
  {
    for (int j = 0; j < grid_size; j++)
    {
      if (allTrees[i][j].x_coord == i && allTrees[i][j].y_coord == j)
      {
        allTrees[i][j].time = time_calculator(x, y, i, j, allTrees[i][j].thickness);
        allTrees[i][j].gain = allTrees[i][j].value / allTrees[i][j].time;
        tree_left++;
        // if we can cut tree in given time than push it in vector
        if (allTrees[i][j].time <= total_time_left)
        {
          left_trees.push_back(allTrees[i][j]);
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
    tree1 s_tree = left_trees[i];
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
  total_price += left_trees[tree_index].value;
  tree_left -= 1; //Todo later we'll consider domino to

  //Todo remove tree and domino and printing path and then change current coordinate of lumber
  int x_coord = left_trees[tree_index].x_coord;
  int y_coord = left_trees[tree_index].y_coord;

  // rmd(x_coord, y_coord); // removed domino
  if (left_trees[tree_index].domino)
    rmd2(x_coord, y_coord);

  printPath(x_coord, y_coord); // printed path

  // removed tree
  allTrees[x_coord][y_coord].x_coord = -1;
  allTrees[x_coord][y_coord].y_coord = -1;
  x = x_coord, y = y_coord;

  return 1;
}

struct dom
{
  int d_index;
  int d_value;
};

int domino_height = 0;

int calculate_domino_value(int i, int j)
{
  tree1 T = allTrees[i][j];
  // TODO check right
  int domino_distance = i + T.height; // respective x or y coordinate till which we can see domino effect
  int k = i + 1;
  while (k < domino_distance && k < grid_size)
  {

    dom d;
    // Now checking tree if present in this distance
    if (allTrees[k][j].x_coord == k && allTrees[k][j].domino == true)
    {
      domino_height = allTrees[k][j].height + k;
      return calculate_domino_value(k, j) + allTrees[k][j].domino_value;
    }

    k++;
  }

  return T.domino_value;
}

int main()
{

  cin >> time_limit >> grid_size >> tree_count;
  tree_left = tree_count;
  total_time_left = time_limit;

  const int g_size = grid_size;

  //    allTrees = new tree [g_size][g_size];

  allTrees = new tree1 *[grid_size];

  tree1 T1;

  for (int i = 0; i < grid_size; i++)
  {
    allTrees[i] = new tree1[grid_size];
    for (int j = 0; j < grid_size; j++)
    {
      T1.x_coord = -1;
      T1.y_coord = -1;
      allTrees[i][j] = T1;
    }
  }

  // taking input
  for (int i = 0; i < tree_count; i++)
  {
    tree1 T;
    cin >> T.x_coord >> T.y_coord >> T.height >> T.thickness >> T.unit_weight >> T.unit_value;

    T.weight = T.unit_weight * T.height * T.thickness;
    T.value = T.unit_value * T.height * T.thickness;

    T.domino = false;
    T.domino_value = 0;
    Trees.push_back(T);

    // we will store info about tree at their coordinate index
    allTrees[T.x_coord][T.y_coord] = T;
  }

  // Will check domino
  for (int i = 0; i < grid_size; i++)
  {
    for (int j = 0; j < grid_size; j++)
    {
      allTrees[i][j].domino_value = 0;
      allTrees[i][j].domino = false;
      tree1 T = allTrees[i][j];
      if (T.x_coord == i && T.y_coord == j)
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
          if (allTrees[k][j].x_coord == k && allTrees[k][j].weight < domino_weight)
          { // pehla tree hona chahiye dusra weight root tree k weight se kam hona chahiye
            // TODO Domino is present
            allTrees[i][j].domino = true; // putting true at root tree
            // allTrees[k][j].domino = true; // putting true at children tree

            // Hum Root ka value append krte hai ye fir search me aa jayega HIGHLIGHT
            allTrees[i][j].domino_value += allTrees[k][j].value;
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
      tree1 T = allTrees[i][j];
      if (T.x_coord == i && T.y_coord == j && T.domino == true)
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
          if (allTrees[k][j].x_coord == k && allTrees[k][j].domino == true)
          {
            // calculate domino value
            allTrees[i][j].value += calculate_domino_value(k, j);
            allTrees[i][j].domino_index = domino_height + i;
            check++;
          }

          k++;
        }
        if (check == 0)
        {
          allTrees[i][j].domino_index = T.height + i;
        }
      }
    }
  }

  while (1)
  {
    if (tree_left <= 0)
    {
      // return 0;
      break;
    }
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
    if (x > 0)
    {
      cout << "move left\n";
      x--;
    }
    else
    {
      total_time_left++;
      while (++x < grid_size - 1 && total_time_left--)
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

  return 0;
}