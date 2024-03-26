#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <algorithm>

//! finds hamiltonian cycle of minimum length
std::pair<int, std::vector<int>> travelingSalesman(std::vector<int> path, std::vector<std::vector<int>> adjacent,
                     std::vector<bool> visited, int length, int numNodes)
{
    const auto curNode = path.back();

    int minLength = std::numeric_limits<int>::max();
    std::vector<int> minPath;
    bool hasVisited = false;
    for(int i = 0; adjacent[curNode].size(); ++i)
    {
        if(adjacent[curNode][i] >= 0 && visited[i] == false)
        {
            hasVisited = true;
            path.emplace_back(i);
            visited[i] = true;
            const auto [newLength, newPath] = travelingSalesman(path, adjacent, visited, length + adjacent[curNode][i], numNodes);
            if(newLength < minLength)
            {
                minLength = newLength;
                minPath = newPath;
            }
            path.pop_back();
            visited[i] = false;
        }
    }

    if(hasVisited == false && path.size() == numNodes)
    {
        const auto startingNode = path.front();
        if(adjacent[curNode][startingNode] >= 0)
        {
            path.emplace_back(startingNode);
            //! go to the starting point if hamiltonian cycle exists
            return std::make_pair(length + startingNode, path);
        }
        else
            //! There is hamiltonian path, but there is no hamiltonian cycle
            return std::make_pair(std::numeric_limits<int>::max(), std::vector<int>());
    }

    //! There is no hamiltonian path in the graph
    if(hasVisited == false)
        return std::make_pair(std::numeric_limits<int>::max(), std::vector<int>());

    return std::make_pair(minLength, minPath);
}

int main()
{
    int numNodes;
    std::cin>>numNodes;
    std::vector<std::vector<int>> adjacent;
    const auto [minLength, minPath] = travelingSalesman({0}, adjacent, std::vector<bool>(numNodes, false), 0, numNodes);

    std::cout<<minLength<<std::endl;
    std::cout<<minPath<<std::endl;
}
