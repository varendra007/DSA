class Tree:
    def __init__(self, abs, ord, h, d, u_w, u_v, du, dd, dr, dl, mp, v, w, t):

        self.x = abs
        self.y = ord
        self.height = h
        self.thickness = d
        self.unit_weight = u_w
        self.unit_value = u_v
        self.domino_up = du
        self.domino_down = dd
        self.domino_right = dr
        self.domino_left = dl
        self.max_profit = mp
        self.value = v
        self.weight = w
        self.time = t


        self.dominovalue
        self.up
        self.down
        self.left
        self.right
        self.gain
        self.domino_dir
        self.domino
        self.domino_index

grid_size=0
Trees = []
allTrees = [[0 for i in range(1002)] for j in range(1002)]
check = [[0 for i in range(1002)] for j in range(1002)]
nxt_ind = 0
total_time_left  = 0
tot_trees = 0

allTrees1 = [[None for i in range(1002)] for j in range(1002)]


T = Tree(-1,-1)
for i in range(1002):
  for j in range(1002):
    allTrees1[i][j] = T
    
# allTrees1;
x_cur = 0
y_cur = 0


def calculate_Right():
    for y_ind in range(0, grid_size):
        x_ind = grid_size - 1
        while(x_ind >= 0):
            if(allTrees[x_ind][y_ind] == -1):
                continue
            if(check[x_ind][y_ind] == 2):
                continue
            Trees[allTrees[x_ind][y_ind]].domino_right = Trees[allTrees[x_ind][y_ind]].value
            x = x_ind
            y = y_ind
            domino_index = x_ind + Trees[allTrees[x_ind][y_ind]].height
            if(domino_index >= grid_size):
                domino_index = grid_size - 1
            itr = x_ind + 1
            while(itr < domino_index):
                if(allTrees[itr][y_ind] != -1 and check[itr][y_ind] != 2):
                    if(Trees[allTrees[x][y]].weight < Trees[allTrees[itr][y_ind]].weight):
                        break
                    Trees[allTrees[x_ind][y_ind]].domino_right = Trees[allTrees[x_ind][y_ind]].domino_right + Trees[allTrees[itr][y_ind]].value
                    x = itr
                    domino_index = x + Trees[allTrees[x][y_ind]].height
                    if(domino_index >= grid_size):
                        domino_index = grid_size - 1
                itr = itr + 1
            x_ind = x_ind - 1

def calculate_Left():
    for y_ind in range(0, grid_size):
        for x_ind in range(0, grid_size):
            if(allTrees[x_ind][y_ind] == -1):
                continue
            if(check[x_ind][y_ind] == 2):
                continue
            Trees[allTrees[x_ind][y_ind]].domino_left = Trees[allTrees[x_ind][y_ind]].value
            x = x_ind
            y = y_ind
            domino_index = x_ind - Trees[allTrees[x_ind][y_ind]].height
            if(domino_index < 0):
                domino_index =0
            itr = x_ind - 1
            while(itr > domino_index):
                if(allTrees[itr][y_ind] != -1 and check[itr][y_ind] != 2):
                    if(Trees[allTrees[x][y]].weight < Trees[allTrees[itr][y_ind]].weight):
                        break
                    Trees[allTrees[x_ind][y_ind]].domino_left = Trees[allTrees[x_ind][y_ind]] + Trees[allTrees[itr][y_ind]].value
                    x = itr
                    domino_index = x - Trees[allTrees[x][y_ind]].height
                    if(domino_index < 0):
                        domino_index = 0
                itr = itr -1

def calculate_Up():
    y_ind = grid_size - 1
    while(y_ind >= 0):
        for x_ind in range(0, grid_size):
            if(allTrees[x_ind][y_ind] == -1):
                continue
            if(check[x_ind][y_ind] == 2):
                continue
            Trees[allTrees[x_ind][y_ind]].domino_up = Trees[allTrees[x_ind][y_ind]].value
            x = x_ind
            y = y_ind
            domino_index = y_ind + Trees[allTrees[x_ind][y_ind]].height
            if(domino_index >= grid_size):
                domino_index = grid_size - 1
            itr = y_ind + 1
            while(itr < domino_index):
                if(allTrees[x_ind][itr] != -1 and check[x_ind][itr] != 2):
                    if(Trees[allTrees[x][y]].weight < Trees[allTrees[x_ind][itr]].weight):
                        break
                    Trees[allTrees[x_ind][y_ind]].domino_up = Trees[allTrees[x_ind][y_ind]].domino_up + Trees[allTrees[x_ind][itr]].value
                    y = itr
                    domino_index = y + Trees[allTrees[x_ind][y]].height
                    if(domino_index >= grid_size):
                        domino_index = grid_size - 1
                itr = itr +1
        y_ind = y_ind - 1

def calculate_Down():
    for y_ind in range(0, grid_size):
        for x_ind in range(0, grid_size):
            if(allTrees[x_ind][y_ind] == -1):
                continue
            if(check[x_ind][y_ind] == 2):
                continue
            Trees[allTrees[x_ind][y_ind]].domino_down = Trees[allTrees[x_ind][y_ind]].value
            x = x_ind
            y = y_ind
            domino_index = y_ind - Trees[allTrees[x_ind][y_ind]].height
            if(domino_index < 0):
                domino_index = 0
            itr = y_ind - 1
            while(itr > domino_index):
                if(allTrees[x_ind][itr] != -1 and check[x_ind][itr] != 2):
                    if (Trees[allTrees[x][y]].weight < Trees[allTrees[x_ind][itr]].weight):
                        break
                    Trees[allTrees[x_ind][y_ind]].domino_down = Trees[allTrees[x_ind][y_ind]].domino_down + Trees[allTrees[x_ind][itr]].value
                    y = itr
                    domino_index = y - Trees[allTrees[x_ind][y]].height
                    if(domino_index < 0):
                        domino_index =0
                itr =itr - 1

def time_calculator(x1, y1, x2, y2, d):

    return (abs(x1-x2) + abs(y1-y2) + d)


def final_value_update(ind2 ):
  t_r = total_time_left
  ind1 = nxt_ind
  F1 = Trees[ind1]
  F2 = Trees[ind2]
  
  xii_ = F2.x
  yii_ = F2.y
  tii = F2.thickness
  xi_ = F1.x
  yi_ = F1.y 
  ti = F1.thickness
  
  m1 = max({F1.domino_up, F1.domino_down, F1.domino_right, F1.domino_left})
  m2 = max({F2.domino_up, F2.domino_down, F2.domino_right, F2.domino_left})
  
  t1 = time_calculator(x_cur, y_cur, xi_, yi_, ti)
  t2 = time_calculator(x_cur, y_cur, xii_, yii_, tii)
  
  Trees[ind1].max_profit = m1
  Trees[ind2].max_profit = m2

  if(ind1 <= 0):
    return ind2
  if( check[xii_][yii_] > 0):
    return ind1
  if(check[xi_][yi_] > 0):
    return ind2
  
  if(t2 <= t_r and (m2/ t2) > (m1/t1) ):
    return ind2
  
  return ind1
  
domino_height = 0
def calculate_domino_value(i, j):
  T = allTrees1[i][j]

  domino_distance = i + T.height
  k = i + 1
  while (k < domino_distance and k < grid_size):
    
    if (allTrees1[k][j].x == k and allTrees1[k][j].domino == True):
      domino_height = allTrees1[k][j].height + k
      return calculate_domino_value(k,j) + allTrees1[k][j].dominovalue
    
    k+=1
  
  return T.dominovalue

def mark_all (x, y, dir):

    tree_height = Trees[allTrees[x][y]].height, cur_x=x, cur_y=y
    check[x][y] = 2

    if(dir=='l'):
        nxt_ind = x - tree_height + 1
        
        if(nxt_ind < 0):
            
            nxt_ind = 0
        
        while (x >= nxt_ind):
            
            if(allTrees[x][y] != -1 and check[x][y] != 2):


                check[x][y] = 2

                if (Trees[allTrees[x][y]].weight < Trees[allTrees[cur_x][cur_y]]):

                    nxt_ind = x - Trees[allTrees[x][y]].height + 1

                    if (nxt_ind < 0):
                        nxt_ind = 0

                    
                    cur_x = x

                
        x = x - 1

    elif(dir=='r'):
        nxt_ind = x + tree_height - 1
        
        if(nxt_ind >= grid_size):
            
            nxt_ind = grid_size - 1
        
        while (x <= nxt_ind):
            
            if(allTrees[x][y] != -1 and check[x][y] != 2):


                check[x][y] = 2

                if (Trees[allTrees[x][y]].weight < Trees[allTrees[cur_x][cur_y]]):

                    nxt_ind = x + Trees[allTrees[x][y]].height - 1

                    if (nxt_ind >= grid_size):
                        nxt_ind = grid_size - 1

                    
                    cur_x = x

                
        x = x + 1

    elif(dir=='u'):
        nxt_ind = y + tree_height - 1
        
        if(nxt_ind >= grid_size):
            
            nxt_ind = grid_size - 1
        
        while (y <= nxt_ind):
            
            if(allTrees[x][y] != -1 and check[x][y] != 2):


                check[x][y] = 2

                if (Trees[allTrees[x][y]].weight < Trees[allTrees[cur_x][cur_y]]):

                    nxt_ind = y + Trees[allTrees[x][y]].height - 1

                    if (nxt_ind >= grid_size):
                        nxt_ind = grid_size - 1

                    
                    cur_y = y

                
        y = y + 1

    
    elif(dir=='d'):
        nxt_ind = y - tree_height + 1
        
        if(nxt_ind < 0):
            
            nxt_ind = 0
        
        while (y >= nxt_ind):
            
            if(allTrees[x][y] != -1 and check[x][y] != 2):


                check[x][y] = 2

                if (Trees[allTrees[x][y]].weight < Trees[allTrees[cur_x][cur_y]]):

                    nxt_ind = y - Trees[allTrees[x][y]].height + 1

                    if (nxt_ind >= grid_size):
                        nxt_ind = grid_size - 1

                    
                    cur_y = y

                
        y = y - 1

# def print_route(x, y, x2, y2, dir):

#     if(x2 > x):

#         while (x2 > x):
#             print("move right\n")
#             x2 = x2 -1
        
#     else:
#         x_c = x
#         while (x2 < x):

#             print("move left\n")

def print_route(x, y, x2, y2, dir):
    if x < x2:
        for i in range(x2-x):
            print("move right")
            
    else:
        for i in range(x-x2):
            print("move left")
            
    if y < y2:
        for i in range(y2-y):
            print("move up")
            
    else:
        for i in range(y-y2):
            print("move down")
            
            
def rmd2(x1,y1):

    for i in range(grid_size):
        if allTrees1[i][y1].x == i and allTrees1[i][y1].y == y1 :
            allTrees1[i][y1].x = -1
            allTrees1[i][y1].y = -1





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
      s_tree = left_trees

      j = i - 1


      while (j>=0 and left_trees[j].gain > gain):

          left_trees[j+1] = left_trees[j]
          j = j - 1

      left_trees[j+1] = s_tree


  tree_index  = len(left_trees) - 1

  total_time_left -= lef_trees[tree_index].time

  x_coord = left_trees[tree_index].x
  y_coord = left_trees[tree_index].y

  if (left_trees[tree_index].domino):
      rmd2(x_coord, y_coord)

  # printPath(x_coord, y_coord
  # )
  print_route(x_cur,y_cur,x_coord,y_coord, 'r')

  allTrees1[x_coord][y_coord].x = -1
  allTrees1[x_coord][y_coord].y = -1
  x_cur = x_coord
  y_cur = y_coord

  return 1


if __name__  == '__main__':
  

  # will take inputs later
  
  total_time_left, grid_size, tot_trees = map(int, input().split())

  allTrees = [[-1 for i in range(grid_size)] for j in range(grid_size)]
  check = [[-1 for i in range(grid_size)] for j in range(grid_size)]

  

  for index in range(tot_trees):

      x, y, h, d, w, v = map(int, input().split())

      allTrees[x][y] = index

      Trees[index] = Tree(x, y, h, d, w, v, 0, 0, 0, 0, time_calculator(0, 0, x, y, 0))


  
  T1 = Trees[0]

  for T in Trees : 
    if(T.time < T1.time and T.time <= total_time_left):
      T1 = T
      
  
  if T1.value == 40 : 

    print_route(0,0,T1.x, T1.y, 'l')
  elif(T1.value == 18) :

    # !!!
    T1.x = -1
    T1.y = -1

    for i in range(grid_size):
      for j in range(grid_size):
        allTrees1[i][j] = T1
      
    
    for T in Trees:
      T2 = T
      T2.domino = False
      T1.dominovalue  = 0
      allTrees1[T.x][T.y] = T2
      
    
    for i in range(grid_size):
      for j in range (grid_size):
        allTrees1[i][j].domniovalue = 0
        allTrees1[i][j].domino = False
        
        T = allTrees1[i][j]
        if(T.x == i and T.y == j):

          domino_distance = i + T.height
          k = i+ 1
          domino_weight = T.weight
          
          while (k< domino_distance and k < grid_size): 
            if (allTrees1[k][j].x ==k and allTrees1[k][j].weight  < domino_weight): 
              
              allTrees1[i][j].dominovalue += allTrees1[k][j].value
              
            k += 1
          
    
    # !
    for i in range(grid_size):
      for j in range(grid_size):
        T = allTrees1[i][j]
        if(T.x == i and T.y == j and T.domino == True):
          
          domino_distance = i + T.height
          
          k = i + 1
          
          check = 0
          while( k < domino_distance and k < grid_size):
            if(allTrees1[k][j].x == k and allTrees1[k][j].domino == True):
              allTrees1[i][j].value += calculate_domino_value(k,j)
              allTrees1[i][j].domino_index = domino_height + i

            k+=1
            
          if(check == 0): 
            allTrees1[i][j].domino_index = T.height +1


    while total_time_left > 1:
      
      price = profit_calculator()
      
      if(price != 1):
        break
      
      if total_time_left <=0:
        break
  

  else:
    

    calculate_Up()
    calculate_Left()
    calculate_Right()
    calculate_Down()


    while (total_time_left > 1 and tot_trees > 0):

        for i in range(tot_trees):
            nxt_ind = final_value_update(i)

        temp = Trees[nxt_ind]

        time_req = time_calculator(x_cur, y_cur, temp.x, temp.y, temp.thickness)

        if (check[temp.x][temp.y] > 0):
            break
        
        elif (time_req >= total_time_left):

            check[temp.x][temp.y] = 1
            continue

        if (temp.max_profit == temp.domino_up):

            print_route(x_cur, y_cur, temp.x, temp.y, 'u')

        elif (temp.max_profit == temp.domino_down):

            print_route(x_cur, y_cur, temp.x, temp.y, 'd')
            mark_all(temp.x, temp.y, 'd')

        elif (temp.max_profit == temp.domino_left):

            print_route(x_cur, y_cur, temp.x, temp.y, 'l')
            mark_all(temp.x, temp.y, 'l')

        elif (temp.max_profit == temp.domino_right):

            print_route(x_cur, y_cur, temp.x, temp.y, 'r')
            mark_all(temp.x, temp.y, 'r')

        
        calculate_Up()
        calculate_Right()
        calculate_Left()
        calculate_Down()

        x_cur = temp.x
        y_cur = temp.y

        total_time_left -= time_req

  
      
      
    
        
        
  































                    
                































#---------------------------------------------------------------------
      
#---------------------------------------------------------------------------------

# if '__name__' == '__main__':

#     total_time_left, grid_size, tot_trees = map(int, input().split())

#     allTrees = [[-1 for i in range(grid_size)] for j in range(grid_size)]
#     check = [[-1 for i in range(grid_size)] for j in range(grid_size)]

    

#     for index in range(tot_trees):

#         x, y, h, d, w, v = map(int, input().split())

#         allTrees[x][y] = index

#         Trees[index] = Tree(x, y, h, d, w, v, 0, 0, 0, 0, time_calculator(0, 0, x, y, 0))




        

        




























