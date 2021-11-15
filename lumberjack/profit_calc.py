

def profit_calculator():

  left_trees = []

  for i in range(grid_size-1):

      for j in range(grid_size-1):

          if (allTrees1[i][j].x == i and allTrees1[i][j].y == j):

              allTrees[i][j].time = time_calculator( x_cur, y_cur, i, j, allTrees[i][j].thickness)
              allTrees[i][j].gain = allTrees1[i][j].value / allTrees[i][j].time

              if (allTrees[i][j].time <= total_time_left):

                  left_trees.append(allTrees1[i][j])


  
  if (len(left_trees)==0):
      
      return -1


  if (total_time_left <= 0):

      return -1

  for i in range(len(left_trees)):

      gain = left_trees[i].gain
      s_tree = left_treei

      j = i - 1


      while (j>=0 and left_trees[j].gain > gain):

          left_trees[j+1] = left_trees[j]
          j = j - 1

      left_trees[j+1] = s_tree


  tree_index  = len(left_trees) - 1

  total_time_left -= lef_trees[tree_index].time

  x_coord = left_trees[tree_index].x
  y_coord = left_trees[tree_index].y

  if (left_trees[tree_index}.domino):
      rmd2(x_coord, y_coord)

  printPath(x_coord, y_coord)

  allTrees1[x_coord][y_coord].x = -1
  allTrees1[x_coord][y_coord].y = -1
  x_cur = x_coord
  y_cur = y_coord

  return 1
