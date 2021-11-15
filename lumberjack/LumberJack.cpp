// #include"pch.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <array>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

enum class Direction
{
	up,
	right,
	down,
	left
};

class Tree
{
public:
	Tree(int xp, int yp, int hp, int dp, int cp, int pp) : x(xp), y(yp), h(hp), d(dp), c(cp), p(pp)
	{
	}
	Tree() {}
	int x, y, h, d, c, p;
	int price()
	{
		return p * h * d;
	}
	int weight()
	{
		return c * h * d;
	}
	array<vector<int>, 4> chains;
	vector<Direction> possible_directions;
};

class Point
{
public:
	//int x, y;
	bool existsTree = 0;
	int tree_key;
};

unordered_map<int, Tree> trees;

//const array<Direction, 4> all_directions{ Direction::up,Direction::right,Direction::down,Direction::left };

void chain_maker(int tree_key, Direction d, vector<int> *chain, Point **points, int grid_size)
{
	switch (d)
	{
	case Direction::up:
	{
		int x = trees[tree_key].x;
		int y = trees[tree_key].y + 1;
		while (y <= grid_size - 1)
		{
			if (points[x][y].existsTree)
			{
				bool isCut = 0;
				for (auto vec_rev_it = chain->rbegin(); vec_rev_it != chain->rend(); vec_rev_it++)
				{
					if (trees[*vec_rev_it].h > y - trees[*vec_rev_it].y && trees[*vec_rev_it].weight() > trees[points[x][y].tree_key].weight())
					{
						isCut = 1;
						break;
					}
				}
				if (isCut)
				{
					chain->emplace_back(points[x][y].tree_key);
					chain_maker(points[x][y].tree_key, d, chain, points, grid_size);
					break;
				}
			}
			y++;
		}
		break;
	}
	case Direction::right:
	{
		int x = trees[tree_key].x + 1;
		int y = trees[tree_key].y;
		while (x <= grid_size - 1)
		{
			if (points[x][y].existsTree)
			{
				bool isCut = 0;
				for (auto vec_rev_it = chain->rbegin(); vec_rev_it != chain->rend(); vec_rev_it++)
				{
					if (trees[*vec_rev_it].h > x - trees[*vec_rev_it].x && trees[*vec_rev_it].weight() > trees[points[x][y].tree_key].weight())
					{
						isCut = 1;
						break;
					}
				}
				if (isCut)
				{
					chain->emplace_back(points[x][y].tree_key);
					chain_maker(points[x][y].tree_key, d, chain, points, grid_size);
					break;
				}
			}
			x++;
		}
		break;
	}
	case Direction::down:
	{
		int x = trees[tree_key].x;
		int y = trees[tree_key].y - 1;
		while (y >= 0)
		{
			if (points[x][y].existsTree)
			{
				bool isCut = 0;
				for (auto vec_rev_it = chain->rbegin(); vec_rev_it != chain->rend(); vec_rev_it++)
				{
					if (trees[*vec_rev_it].h > trees[*vec_rev_it].y - y && trees[*vec_rev_it].weight() > trees[points[x][y].tree_key].weight())
					{
						isCut = 1;
						break;
					}
				}
				if (isCut)
				{
					chain->emplace_back(points[x][y].tree_key);
					chain_maker(points[x][y].tree_key, d, chain, points, grid_size);
					break;
				}
			}
			y--;
		}
		break;
	}
	case Direction::left:
	{
		int x = trees[tree_key].x - 1;
		int y = trees[tree_key].y;
		while (x >= 0)
		{
			if (points[x][y].existsTree)
			{
				bool isCut = 0;
				for (auto vec_rev_it = chain->rbegin(); vec_rev_it != chain->rend(); vec_rev_it++)
				{
					if (trees[*vec_rev_it].h > trees[*vec_rev_it].x - x && trees[*vec_rev_it].weight() > trees[points[x][y].tree_key].weight())
					{
						isCut = 1;
						break;
					}
				}
				if (isCut)
				{
					chain->emplace_back(points[x][y].tree_key);
					chain_maker(points[x][y].tree_key, d, chain, points, grid_size);
					break;
				}
			}
			x--;
		}
		break;
	}
	}
}

void delete_chain(vector<int> chain, Point **points, int grid_size)
{
	for (auto vec_it = chain.begin(); vec_it != chain.end(); vec_it++)
	{
		points[trees[*vec_it].x][trees[*vec_it].y].existsTree = 0;
	}
	for (auto map_it = trees.begin(); map_it != trees.end(); map_it++)
	{
		for (auto vec_it = chain.begin(); vec_it != chain.end(); vec_it++)
		{
			if (map_it->first != *vec_it)
			{
				for (Direction d : map_it->second.possible_directions)
				{
					if (find(map_it->second.chains[static_cast<int>(d)].begin(), map_it->second.chains[static_cast<int>(d)].end(), *vec_it) !=
							map_it->second.chains[static_cast<int>(d)].end())
					{
						map_it->second.chains[static_cast<int>(d)].clear();
						map_it->second.chains[static_cast<int>(d)].emplace_back(map_it->first);
						chain_maker(map_it->first, d, &(map_it->second.chains[static_cast<int>(d)]), points, grid_size);
					}
				}
			}
		}
	}
	for (auto vec_it = chain.begin(); vec_it != chain.end(); vec_it++)
	{
		trees.erase(*vec_it);
	}
}

void get_possible_directions(Tree &t, int grid_size)
{
	if (t.x != grid_size - 1)
		t.possible_directions.emplace_back(Direction::right);
	if (t.x != 0)
		t.possible_directions.emplace_back(Direction::left);
	if (t.y != grid_size - 1)
		t.possible_directions.emplace_back(Direction::up);
	if (t.y != 0)
		t.possible_directions.emplace_back(Direction::down);
}

int main()
{
	int time, grid_size, no_of_trees;
	cin >> time >> grid_size >> no_of_trees;
	Point **points = new Point *[grid_size];
	for (int i = 0; i < grid_size; i++)
		points[i] = new Point[grid_size];
	for (int i = 0; i < no_of_trees; i++)
	{
		int x, y, h, d, c, p;
		cin >> x >> y >> h >> d >> c >> p;
		trees[i] = Tree(x, y, h, d, c, p);
		points[x][y].existsTree = 1;
		points[x][y].tree_key = i;
	}

	int curr_x(0), curr_y(0);
	for (int i = 0; i < no_of_trees; i++)
	{
		get_possible_directions(trees[i], grid_size);
		for (Direction d : trees[i].possible_directions)
		{
			trees[i].chains[static_cast<int>(d)].emplace_back(i);
			chain_maker(i, d, &(trees[i].chains[static_cast<int>(d)]), points, grid_size);
		}
	}
	while (time > 0 && !trees.empty())
	{
		double max_ratio = 0;
		bool isSet(0);
		int max_ratio_tree_key;
		int temp_time;
		//bool isChain;
		//int total_profit;
		Direction chain_dir;
		vector<int> chain;
		for (auto it = trees.begin(); it != trees.end(); it++)
		{
			int temp_time_local = abs(curr_x - it->second.x) + abs(curr_y - it->second.y) + it->second.d;
			if (temp_time_local > time)
				continue;
			double ratio;
			Direction chain_dir_local;
			int profit = 0;
			vector<int> chain_local;
			for (Direction d : it->second.possible_directions)
			{
				int profit_local = 0;
				for (auto vec_it = it->second.chains[static_cast<int>(d)].begin(); vec_it != it->second.chains[static_cast<int>(d)].end(); vec_it++)
				{
					profit_local += trees[*vec_it].price();
				}
				if (profit_local > profit)
				{
					profit = profit_local;
					chain_dir_local = d;
					chain_local = (it->second.chains[static_cast<int>(d)]);
				}
			}
			ratio = static_cast<double>(profit) / temp_time_local;
			if (ratio > max_ratio)
			{
				isSet = 1;
				max_ratio = ratio;
				max_ratio_tree_key = it->first;
				temp_time = temp_time_local;
				//total_profit = profit;
				chain_dir = chain_dir_local;
				chain = chain_local;
			}
		}
		if (isSet)
		{
			if (curr_x < trees[max_ratio_tree_key].x)
			{
				for (int i = 0; i < trees[max_ratio_tree_key].x - curr_x; i++)
					cout << "move right\n";
			}
			else
			{
				for (int i = 0; i < curr_x - trees[max_ratio_tree_key].x; i++)
					cout << "move left\n";
			}
			if (curr_y < trees[max_ratio_tree_key].y)
			{
				for (int i = 0; i < trees[max_ratio_tree_key].y - curr_y; i++)
					cout << "move up\n";
			}
			else
			{
				for (int i = 0; i < curr_y - trees[max_ratio_tree_key].y; i++)
					cout << "move down\n";
			}
			switch (chain_dir)
			{
			case Direction::down:
				cout << "cut down\n";
				break;
			case Direction::left:
				cout << "cut left\n";
				break;
			case Direction::right:
				cout << "cut right\n";
				break;
			case Direction::up:
				cout << "cut up\n";
				break;
			}
			curr_x = trees[max_ratio_tree_key].x;
			curr_y = trees[max_ratio_tree_key].y;
			delete_chain(chain, points, grid_size);
			time -= temp_time;
		}
		else
			break;
	}

	return 0;
}
