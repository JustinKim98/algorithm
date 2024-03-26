#include <vector>

std::vector<std::vector<int>> clockConfig = {{0,1,2},{3,7,9,1},{4,10,14,15},{0,4,5,6,7},{6,7,8,10,12},{0,2,14,15},{3,14,15},
    {4,5,7,14,15},{1,2,3,4,5},{3,4,5,9,13}};

std::vector<int> clocks(10);

void push_button(int button)
{
    for(auto clockId : clockConfig[button])
    {
        clocks[clockId] += 3;
        if(clocks[clockId] == 15)
            clocks[clockId] = 3;
    }

    
}