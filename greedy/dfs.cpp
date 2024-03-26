#include <iostream>
#include <vector>

int adjacentMatrix[10][10];
std::vector<bool> visited(10, false);


//! DFS algorithm implemented in recursive manner
void dfs(int nodeNum)
{
    std::cout<<"visited:"<<nodeNum<<std::endl; 
    for(int i =0; i < 10; ++i)
    {
        if(adjacentMatrix[nodeNum][i] > 0 && visited[nodeNum] == false)
        {
            dfs(nodeNum);
        }
    }
}

//! DFS algorithm implemented in iterative manner
void iterativeDfs(int startNode)
{
    std::vector<int> stack;

    stack.emplace_back(startNode);
    while(!stack.empty())
    {
        auto& currentNode = stack.front();
        visited[currentNode] = true;

        bool found = false;
        for(int i = 0; i < 10 && found==false; ++i)
        {
            if(adjacentMatrix[currentNode][i] > 0 && visited[i] == false)
            {
                stack.emplace_back(i);
                found = true;
            }
        }

        if(found == false)
            stack.pop_back();
    }
}

int main()
{


}