#include <vector>
#include <iostream>
#include <optional>

//! input : grid and size of the grid
std::optional<std::pair<int, int>> getTopLeft(const std::vector<std::vector<char>>& grid)
{
    const auto numRows = grid.size();
    const auto numCols = grid[0].size();
    for(int i =0; i < numRows; ++i)
        for(int j =0; j < numCols; ++j)
        {
            if(grid[i][j] == '.')
                return std::make_pair(i, j);
        }
    return {};
}

//! input : grid and position in the grid
//! *
//! * *
bool placeBlock0(std::vector<std::vector<char>>& grid, int row, int col)
{
    if(row+1 >= grid.size() || col+1 >= grid[0].size())
        return false;

    if(grid[row][col] == '.' && grid[row + 1][col] == '.' && grid[row+1][col+1] == '.')
    {
        grid[row][col] = '#';
        grid[row+1][col] = '#';
        grid[row+1][col+1] = '#';
        return true;
    }

    return  false;
}

//! input : grid and position in the grid
//!   *
//! * *
bool placeBlock1(std::vector<std::vector<char>>& grid, int row, int col)
{

    if(row+1 >= grid.size() || col-1 < 0)
        return false;

    if(grid[row][col] == '.' && grid[row + 1][col] == '.' && grid[row+1][col-1] == '.')
    {
        grid[row][col] = '#';
        grid[row+1][col] = '#';
        grid[row+1][col-1] = '#';
        return true;
    }

    return  false;
}

//! input : grid and position in the grid
//! * *
//!   *
bool placeBlock2(std::vector<std::vector<char>>& grid, int row, int col)
{
    if(row+1 >= grid.size() || col+1 >= grid[0].size())
        return false;

    if(grid[row][col] == '.' && grid[row + 1][col + 1] == '.' && grid[row][col+1] == '.')
    {
        grid[row][col] = '#';
        grid[row][col+1] = '#';
        grid[row+1][col+1] = '#';
        return true;
    }

    return  false;
}

//! input : grid and position in the grid
//! * *
//! *
bool placeBlock3(std::vector<std::vector<char>>& grid, int row, int col)
{
    if(row+1 >= grid.size() || col+1 >= grid[0].size())
        return false;

    if(grid[row][col] == '.' && grid[row+1][col] == '.' && grid[row][col+1] == '.')
    {
        grid[row][col] = '#';
        grid[row][col+1] = '#';
        grid[row+1][col] = '#';
        return true;
    }

    return  false;
}

bool isFeasible(std::vector<std::vector<char>>& grid)
{
    int numEmpty = 0;
    for(auto vec : grid)
        for(auto ch : vec)
            if(ch == '.')
                numEmpty += 1;

    if(numEmpty % 3 != 0)
        return 0;

    return numEmpty;
}

void printGrid(std::vector<std::vector<char>>& grid)
{
    int numEmpty = 0;
    for(auto vec : grid)
    {
        for(auto ch : vec)
            std::cout<<ch <<" ";
        std::cout<<std::endl;
    }
}

int search(std::vector<std::vector<char>>& grid)
{
    auto topLeft = getTopLeft(grid);
    if(!topLeft)
        return 1;

    const auto [left, right] = topLeft.value();
    int numMethods = 0;
    auto grid0 = grid;
    if(placeBlock0(grid0, left, right))
        numMethods += search(grid0);

    auto grid1 = grid;
    if(placeBlock1(grid1, left, right))
        numMethods += search(grid1);
    
    auto grid2 = grid;
    if(placeBlock2(grid2, left, right))
        numMethods += search(grid2);

    auto grid3 = grid;
    if(placeBlock3(grid3, left, right))
        numMethods += search(grid3);
    
    return numMethods;
}

int main()
{
    int rows, cols;
    std::cin>>rows;
    std::cin>>cols;

    std::vector<std::vector<char>> grid(rows, std::vector<char>(cols));

    for(int i =0; i < rows; ++i)
    {
        std::string input;
        std::cin>>input;
        for(int j = 0; j < cols; ++j)
            grid[i][j] = input[j];
    }

    // std::cout<<"grid layout"<<std::endl;
    // printGrid(grid);
    if(!isFeasible(grid))
    {
        std::cout<<0<< std::endl;
        return 0;
    }

    int numMethods = search(grid);
    std::cout<<numMethods;
}