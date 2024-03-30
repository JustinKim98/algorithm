#include <iostream>
#include <vector>
#include <tuple>
#include <deque>
#include <algorithm>

int visited[100000];

int getParent(int a)
{
    if (visited[a] == a)
        return a;

    return getParent(visited[a]);
}

bool unionParent(int a, int b)
{
    auto aParent = getParent(a);
    auto bParent = getParent(b);

    if (aParent == bParent)
        return false;

    if (aParent > bParent)
        visited[aParent] = bParent;
    else
        visited[bParent] = aParent;
    return true;
}

int main()
{
    int numVertices;
    std::cin >> numVertices;
    std::vector<std::tuple<int, int, int, int>> points(numVertices);

    for (int i = 0; i < numVertices; ++i)
    {
        int x, y, z;
        std::cin >> x >> y >> z;
        points[i] = std::make_tuple(i, x, y, z);
        visited[i] = i;
    }

    std::deque<std::tuple<int, int, int>> edges; // from, to, length

    /// Emplace edges adjecent on x axis
    std::sort(points.begin(), points.end(), [](auto lhs, auto rhs)
              { return std::get<1>(lhs) < std::get<1>(rhs); });
    for (int i = 0; i < numVertices - 1; ++i)
    {
        edges.emplace_back(std::get<0>(points[i]), std::get<0>(points[i + 1]), std::get<1>(points[i + 1]) - std::get<1>(points[i]));
    }

    /// Emplace edges adjecent on y axis
    std::sort(points.begin(), points.end(), [](auto lhs, auto rhs)
              { return std::get<2>(lhs) < std::get<2>(rhs); });
    for (int i = 0; i < numVertices - 1; ++i)
    {
        edges.emplace_back(std::get<0>(points[i]), std::get<0>(points[i + 1]), std::get<2>(points[i + 1]) - std::get<2>(points[i]));
    }

    /// Emplace edges adjecent on z axis
    std::sort(points.begin(), points.end(), [](auto lhs, auto rhs)
              { return std::get<3>(lhs) < std::get<3>(rhs); });
    for (int i = 0; i < numVertices - 1; ++i)
    {
        edges.emplace_back(std::get<0>(points[i]), std::get<0>(points[i + 1]), std::get<3>(points[i + 1]) - std::get<3>(points[i]));
    }

    /// Kruskal's algorithm
    std::sort(edges.begin(), edges.end(), [](auto lhs, auto rhs)
              { return std::get<2>(lhs) < std::get<2>(rhs); });

    std::int64_t cost = 0;
    int edgeCnt = 0;
    int edgeIdx = 0;
    // std::cout << "edgeSize : " << edges.size() << "\n";
    while (edgeCnt < numVertices - 1)
    {
        auto [from, to, dist] = edges[edgeIdx];
        if (unionParent(from, to))
        {
            // std::cout << "connect (" << from << ", " << to << ")" << std::endl;
            cost += dist;
            edgeCnt += 1;
        }
        edgeIdx += 1;
    }

    std::cout << cost << std::endl;

    return 0;
}
