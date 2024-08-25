#include <iostream>
#include <vector>

struct Edge
{
    int From, To;
    std::uint64_t Weight;

    bool operator==(const Edge &edge)
    {
        return From == edge.From && To == edge.To && Weight == edge.Weight;
    }

    bool operator!=(const Edge &edge)
    {
        return !this->operator==(edge);
    }
};

std::vector<int> graph;
std::vector<int> rank;

int findParent(int id)
{
    if (graph[id] == -1)
        return id;

    return graph[id] = findParent(graph[id]);
}

bool hasCommonParent(int from, int to)
{
    return findParent(from) == findParent(to);
}

void unify(int from, int to)
{
    const auto fromParent = findParent(from);
    const auto toParent = findParent(to);

    if (fromParent == toParent)
        return;

    if (rank[fromParent] < rank[toParent])
        graph[fromParent] = toParent;
    if (rank[toParent] < rank[fromParent])
        graph[toParent] = fromParent;
    if (rank[fromParent] == rank[toParent])
    {
        graph[fromParent] = toParent;
        rank[toParent] += 1;
    }
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);

    int numNodes, numEdges;
    std::cin >> numNodes >> numEdges;

    std::vector<Edge> upEdges;
    std::vector<Edge> downEdges;

    upEdges.reserve(numEdges + 1);
    downEdges.reserve(numEdges + 1);

    for (int i = 0; i < numEdges + 1; ++i)
    {
        int from, to;
        std::uint64_t isDownEdge;

        std::cin >> from >> to >> isDownEdge;

        if (isDownEdge)
            downEdges.emplace_back(Edge{from, to, isDownEdge});
        else
            upEdges.emplace_back(Edge{from, to, isDownEdge});
    }

    graph = std::vector<int>(numNodes + 1, -1);
    rank = std::vector<int>(numNodes + 1, 0);
    
    std::uint64_t numUpEdges = 0;
    for (const auto &upEdge : upEdges)
    {
        if (!hasCommonParent(upEdge.From, upEdge.To))
        {
            unify(upEdge.From, upEdge.To);
            numUpEdges += 1;
        }
    }

    graph = std::vector<int>(numNodes + 1, -1);
    rank = std::vector<int>(numNodes + 1, 0);

    for (const auto &downEdge : downEdges)
    {
        if (!hasCommonParent(downEdge.From, downEdge.To))
        {
            unify(downEdge.From, downEdge.To);
        }
    }

    std::uint64_t numUpEdgesForShortest = 0;
    for (const auto &upEdge : upEdges)
    {
        if (!hasCommonParent(upEdge.From, upEdge.To))
        {
            unify(upEdge.From, upEdge.To);
            numUpEdgesForShortest += 1;
        }
    }

    std::cout << numUpEdges * numUpEdges - numUpEdgesForShortest * numUpEdgesForShortest;

    return 0;
}
