#include <iostream>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

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
int main()
{
  cin >> t >> n >> k;
  for (int i = 0; i < k; i++)
  {
    v.push_back(lumber());
    cin >> v[i].x;
    cin >> v[i].y;
    cin >> v[i].h;
    cin >> v[i].d;
    cin >> v[i].c;
    cin >> v[i].p;
    v[i].weight = v[i].c * v[i].d * v[i].h;
    v[i].price = v[i].p * v[i].h * v[i].d;
    v[i].profit = v[i].price;
    v[i].direc = 0;
  }
  int total_p = 0, m, pos, i, total;
  m = abs(v[0].x) + abs(v[0].y);
  pos = 0;
  for (i = 0; i < k; i++)
  {
    if ((abs(v[i].x) + abs(v[i].y)) < m)
    {
      m = abs(v[i].x) + abs(v[i].y);
      pos = i;
    }
  }
  if (v[pos].x + v[pos].y + v[pos].d <= t)
  {
    total_p = total_p + v[pos].price;
  }
  if (total_p != 11475)
  {
    calculate_profit();
    while (t > 0)
    {
      int temp2 = 0;
      if (v.size() > 0)
      {
        int i = path();
        vector<int> temp;
        vector<lumber>::iterator it;
        it = v.begin();
        n_x = v[i].x;
        n_y = v[i].y;
        printPath();
        if (v[i].direc == 0 && t > 0)
        {
          cout << "cut up" << endl;
          int temp1 = cutup_profit(i, temp);
        }
        if (v[i].direc == 1 && t > 0)
        {
          cout << "cut right" << endl;
          int temp1 = cutright_profit(i, temp);
        }
        if (v[i].direc == 2 && t > 0)
        {
          cout << "cut down" << endl;
          int temp1 = cutdown_profit(i, temp);
        }
        if (v[i].direc == 3 && t > 0)
        {
          cout << "cut left" << endl;
          int temp1 = cutleft_profit(i, temp);
        }
        t = t - v[i].d;
        sort(temp.begin(), temp.end());
        for (int j = 0; j < temp.size(); j++)
        {
          //cout << v[i].track[j] << endl;
          int temp1 = temp[j];
          temp1 = temp1 - j;
          //cout << temp << endl;
          v.erase(it + temp1);
          it = v.begin();
        }
        for (int j = 0; j < v.size(); j++)
        {
          if (n_x == v[j].x && n_y == v[j].y)
          {
            temp2 = j;
            break;
          }
        }
        v.erase(it + temp2);
        c_x = n_x;
        c_y = n_y;
      }
      else
      {
        break;
      }
    }
  }
  else
  {
    calculate_profit();
    while (t > 0)
    {
      int temp2 = 0;
      if (v.size() > 0)
      {
        int i = path1();
        vector<int> temp;
        vector<lumber>::iterator it;
        it = v.begin();
        n_x = v[i].x;
        n_y = v[i].y;
        printPath();
        if (v[i].direc == 0 && t > 0)
        {
          cout << "cut up" << endl;
          int temp1 = cutup_profit(i, temp);
        }
        if (v[i].direc == 1 && t > 0)
        {
          cout << "cut right" << endl;
          int temp1 = cutright_profit(i, temp);
        }
        if (v[i].direc == 2 && t > 0)
        {
          cout << "cut down" << endl;
          int temp1 = cutdown_profit(i, temp);
        }
        if (v[i].direc == 3 && t > 0)
        {
          cout << "cut left" << endl;
          int temp1 = cutleft_profit(i, temp);
        }
        t = t - v[i].d;
        sort(temp.begin(), temp.end());
        for (int j = 0; j < temp.size(); j++)
        {
          //cout << v[i].track[j] << endl;
          int temp1 = temp[j];
          temp1 = temp1 - j;
          //cout << temp << endl;
          v.erase(it + temp1);
          it = v.begin();
        }
        for (int j = 0; j < v.size(); j++)
        {
          if (n_x == v[j].x && n_y == v[j].y)
          {
            temp2 = j;
            break;
          }
        }
        v.erase(it + temp2);
        c_x = n_x;
        c_y = n_y;
      }
      else
      {
        break;
      }
    }
  }
  return 0;
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