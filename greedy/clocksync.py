import copy

clocks_config = [[0,1,2],[3,7,9,1],[4,10,14,15],[0,4,5,6,7],[6,7,8,10,12],[0,2,14,15],[3,14,15],\
    [4,5,7,14,15],[1,2,3,4,5],[3,4,5,9,13]]

def change_clock(clocks, num):
    for clock_num in clocks_config[num]:
        clocks[clock_num] += 3
        if clocks[clock_num] == 15:
            clocks[clock_num] = 3
    return clocks

def is_complete(clocks):
    #print(clocks)
    for clock in clocks:
        if clock != 12:
            return False
    return True


def solve(clocks, depth):
    if depth == 10:
        if is_complete(clocks):
            return 0
        else:
            return 1000000

    min_val = 1000000
    for i in range(0,4):
        min_val = min(min_val, i + solve(copy.deepcopy(clocks), depth + 1))
        clocks = change_clock(clocks, depth)
            
    return min_val
    

if __name__ == '__main__':
    clocks=list()
    for i in range(0, 16):
        clocks.append(int(input()))
        #print(clocks)
    min_depth = solve(clocks, 0)

    print(min_depth)