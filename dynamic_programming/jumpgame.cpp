#include <iostream>
#include <vector>
#include <limits>
#define MAX std::numeric_limits<int>::max()

int solve(const std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& smallest, int xPos, int yPos)
{
    if(smallest[yPos][xPos] < MAX)
        return smallest[yPos][xPos];

    if(xPos == grid[0].size() - 1 && yPos == grid.size() - 1)
        return 0;
    
    int dist = grid[yPos][xPos];

    int belowMin = MAX;
    int rightMin = MAX;
    if(xPos + dist < grid[0].size())
    {
        belowMin = solve(grid, smallest, xPos + dist, yPos);
        if(belowMin + dist > 0)
            belowMin += dist;
    }


    if(yPos + dist < grid.size())
    {
        rightMin = solve(grid, smallest, xPos, yPos + dist);
        if(rightMin + dist > 0)
            rightMin += dist;
    }


    int smallestDist = std::min(belowMin, rightMin);
    smallest[yPos][xPos] = smallestDist;
    return smallestDist;
}

int main()
{
    int n;
    std::cin>>n;
    std::vector<std::vector<int>> grid(n, std::vector<int>(n));
    std::vector<std::vector<int>> smallest(n, std::vector<int>(n, MAX));

    for(int i =0; i < n; ++i)
        for(int j = 0; j < n; ++j)
        {
            int num;
            std::cin>>num;
            grid[i][j] = num;
        }


    int answer = solve(grid, smallest, 0, 0);
    std::cout<<answer<<std::endl;

    return 0;
}