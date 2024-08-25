#include <iostream>
#include <algorithm>
#include <deque>

int network[1000][1000];

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

    if (from == to)
        return;

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

    int numVertices, numPreconnected;
    std::cin >> numVertices >> numPreconnected;

    std::vector<std::pair<int, int>> preConnected;
    preConnected.reserve(numPreconnected);

    for (int i = 0; i < numPreconnected; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        preConnected.emplace_back(std::make_pair(a - 1, b - 1));
    }

    edges.reserve(numVertices * numVertices);
    for (int i = 0; i < numVertices; ++i)
        for (int j = 0; j < numVertices; ++j)
        {
            std::uint64_t weight;
            std::cin >> weight;
            network[i][j] = weight;
            if (j > i && i != 0 && j != 0)
                edges.emplace_back(Edge{i, j, weight});
        }

    graph = std::vector<int>(numVertices, -1);
    rank = std::vector<int>(numVertices, 0);

    for (int i = 0; i < numPreconnected; ++i)
    {
        const auto [from, to] = preConnected[i];
        addEdge(Edge{from, to, static_cast<std::uint64_t>(network[from][to])});
    }

    // sort the edges
    auto sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const Edge &left, const Edge &right)
              { return left.Weight < right.Weight; });

    int minEdgeIdx = 0;
    std::uint64_t totalWeight = 0;

    std::vector<Edge> edgesToConnect;
    edgesToConnect.reserve(numVertices * numVertices / 2);
    for (int i = 0; i < sortedEdges.size(); ++i)
    {
        auto minimumEdge = sortedEdges[i];

        // std::cout << "parent of " << minimumEdge.From << " : " << findParent(minimumEdge.From) << "\n";
        // std::cout << "parent of " << minimumEdge.To << " : " << findParent(minimumEdge.To) << "\n";

        if (!hasCommonParent(minimumEdge.From, minimumEdge.To))
        {
            addEdge(minimumEdge);
            edgesToConnect.emplace_back(minimumEdge);
            totalWeight += minimumEdge.Weight;
        }
    }

    std::cout << totalWeight << " " << edgesToConnect.size() << "\n";
    for (const auto &e : edgesToConnect)
    {
        std::cout << e.From + 1 << " " << e.To + 1 << "\n";
    }

    return 0;
}
