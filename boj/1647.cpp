#include <iostream>
#include <algorithm>
#include <deque>

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

std::vector<Edge> edges;
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

void addEdge(Edge edge)
{
    // std::cout << "add from : " << edge.From << " to : " << edge.To << "\n";
    const auto from = findParent(edge.From);
    const auto to = findParent(edge.To);

    if (rank[from] < rank[to])
        graph[from] = to;

    if (rank[from] > rank[to])
        graph[to] = from;

    if (rank[from] == rank[to])
    {
        graph[from] = to;
        rank[to] += 1;
    }
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);

    int numVertices, numEdges;
    std::cin >> numVertices >> numEdges;

    edges.reserve(numEdges);
    for (int i = 0; i < numEdges; ++i)
    {
        int from, to;
        std::uint64_t weight;
        std::cin >> from >> to >> weight;
        edges.emplace_back(Edge{from, to, weight});
    }

    auto sortedEdges = edges;

    // sort the edges
    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const Edge &left, const Edge &right)
              { return left.Weight < right.Weight; });

    graph = std::vector<int>(numVertices, -1);
    rank = std::vector<int>(numVertices, 0);

    int minEdgeIdx = 0;
    std::uint64_t totalWeight = 0;
    std::uint64_t largestEdge = 0;
    for (int i = 0; i < numEdges; ++i)
    {
        auto minimumEdge = sortedEdges[i];

        // std::cout << "parent of " << minimumEdge.From << " : " << findParent(minimumEdge.From) << "\n";
        // std::cout << "parent of " << minimumEdge.To << " : " << findParent(minimumEdge.To) << "\n";

        if (!hasCommonParent(minimumEdge.From, minimumEdge.To))
        {
            addEdge(minimumEdge);
            totalWeight += minimumEdge.Weight;
            if (largestEdge < minimumEdge.Weight)
                largestEdge = minimumEdge.Weight;
        }
    }

    std::cout << totalWeight - largestEdge << "\n";
    return 0;
}
