#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

int parent[10000];
int numVertices, numEdges;

int getParent(int idx)
{
    if (parent[idx] == idx)
        return idx;

    return getParent(parent[idx]);
}

bool unionParents(int left, int right)
{
    auto leftParent = getParent(left);
    auto rightParent = getParent(right);

    if (leftParent == rightParent)
        return false;

    if (leftParent > rightParent)
        parent[leftParent] = rightParent;
    else
        parent[rightParent] = leftParent;

    return true;
}

int kruskal(std::vector<std::tuple<int, int, int>> &edges)
{
    int edgeCnt = 0;
    int totalCost = 0;

    std::sort(edges.begin(), edges.end(), [](auto left, auto right)
              { return std::get<2>(left) < std::get<2>(right); });

    int i = 0;
    while (edgeCnt < numVertices - 1)
    {
        auto [leftIdx, rightIdx, cost] = edges[i++];
        if (unionParents(leftIdx, rightIdx))
        {
            edgeCnt += 1;
            totalCost += cost;
        }
    }

    return totalCost;
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    std::cin >> numVertices >> numEdges;
    std::vector<std::tuple<int, int, int>> edges(numEdges);
    for (int i = 0; i < numVertices; ++i)
        parent[i] = i;

    for (int i = 0; i < numEdges; ++i)
    {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        edges[i] = std::make_tuple(from, to, cost);
    }

    std::cout << kruskal(edges) << "\n";
}
