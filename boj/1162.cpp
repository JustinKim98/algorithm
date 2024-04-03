#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <limits>
#include <cstdint>

int numCities, numRoads, maxConstructions;
std::vector<std::deque<std::pair<int, std::uint64_t>>> graph;

struct Point
{
    int Id;
    int ConstructedRoads;
    std::uint64_t Cost;

    bool operator<(const Point &point) const
    {
        return Cost < point.Cost;
    }
    bool operator>(const Point &point) const
    {
        return Cost > point.Cost;
    }
};

std::priority_queue<Point, std::vector<Point>, std::greater<>>
    queue;

// Vertices, constructed roads
std::uint64_t minCost[10001][21];
bool visited[10001][21];

void dijkstra()
{
    queue.emplace(Point{1, 0, 0});
    minCost[1][0] = 0;

    while (!queue.empty())
    {
        auto point = queue.top();
        queue.pop();
        visited[point.Id][point.ConstructedRoads] = true;

        // std::cout << "point : " << point.Id << " constructions : " << point.ConstructedRoads << " cost : " << point.Cost << "\n";
        if (minCost[point.Id][point.ConstructedRoads] < point.Cost)
            continue;

        for (auto [nextId, cost] : graph[point.Id])
        {
            if (!visited[nextId][point.ConstructedRoads] && minCost[nextId][point.ConstructedRoads] > point.Cost + cost)
            {
                // std::cout << "hello\n";
                minCost[nextId][point.ConstructedRoads] = point.Cost + cost;
                queue.emplace(Point{nextId, point.ConstructedRoads, minCost[nextId][point.ConstructedRoads]});
            }

            if (point.ConstructedRoads < maxConstructions && !visited[nextId][point.ConstructedRoads + 1] &&
                minCost[nextId][point.ConstructedRoads + 1] > point.Cost)
            {
                // std::cout << "hello2\n";
                minCost[nextId][point.ConstructedRoads + 1] = point.Cost;
                queue.emplace(Point{nextId, point.ConstructedRoads + 1, minCost[nextId][point.ConstructedRoads + 1]});
            }
        }
    }
}

int main()
{
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios::sync_with_stdio(false);
    std::cin >> numCities >> numRoads >> maxConstructions;
    graph.clear();
    graph.resize(numCities + 1);

    for (int i = 0; i < numRoads; ++i)
    {
        int from, to;
        std::uint64_t cost;
        std::cin >> from >> to >> cost;
        graph[from].emplace_back(std::make_pair(to, cost));
        graph[to].emplace_back(std::make_pair(from, cost));
    }

    for (int i = 0; i <= numCities; ++i)
    {
        for (int j = 0; j <= maxConstructions; ++j)
        {
            visited[i][j] = false;
            minCost[i][j] = std::numeric_limits<std::uint64_t>::max();
        }
    }

    dijkstra();

    std::uint64_t totalCost = std::numeric_limits<std::uint64_t>::max();
    for (int i = 0; i <= maxConstructions; ++i)
    {
        totalCost = std::min(totalCost, minCost[numCities][i]);
    }

    std::cout << totalCost << "\n";
    return 0;
}
