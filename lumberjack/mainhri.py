
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
