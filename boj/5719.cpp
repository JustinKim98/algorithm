#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <unordered_set>
#include <limits>

int numLocations, numRoads;
int begin, end;

bool visited[500];
bool visited2[500];
bool isInShortestPath[500][500];
int minCost[500];

// int adj[500][500];

std::vector<std::deque<std::pair<int, int>>>
    graph;
std::vector<std::deque<std::pair<int, int>>> reverseGraph;

struct Point
{
    bool operator<(const Point &rhs) const
    {
        return Cost < rhs.Cost;
    }

    bool operator>(const Point &rhs) const
    {
        return Cost > rhs.Cost;
    }

    int Id;
    int Cost;
};

void dijkstra(int beginId, int endId)
{
    std::priority_queue<Point, std::vector<Point>, std::greater<>> queue;
    queue.emplace(Point{beginId, 0});
    minCost[beginId] = 0;
    while (!queue.empty())
    {
        Point curPoint = queue.top();
        queue.pop();
        visited[curPoint.Id] = true;

        if (curPoint.Id == endId)
            return;

        if (curPoint.Cost > minCost[curPoint.Id])
            continue;

        // std::cout << "visit : " << curPoint.Id << "\n";

        for (auto [nextId, cost] : graph[curPoint.Id])
        {
            if (visited[nextId] || isInShortestPath[curPoint.Id][nextId])
                continue;

            // std::cout << "check : " << nextId << " cost : " << minCost[curPoint.Id] + cost << "\n";
            if (curPoint.Cost + cost < minCost[nextId])
            {
                // std::cout << "emplace : " << nextId << "\n";
                minCost[nextId] = curPoint.Cost + cost;
                reverseGraph[nextId].clear();
                reverseGraph[nextId].emplace_back(std::make_pair(curPoint.Id, cost));
                queue.emplace(Point{nextId, curPoint.Cost + cost});
            }
            if (curPoint.Cost + cost == minCost[nextId])
            {
                reverseGraph[nextId].emplace_back(std::make_pair(curPoint.Id, cost));
            }
        }
    }
}

void logShortestPath(int endId, int beginId)
{
    std::queue<int> idQueue;
    idQueue.emplace(endId);
    while (!idQueue.empty())
    {
        auto curId = idQueue.front();
        idQueue.pop();

        auto curCost = minCost[curId];
        for (auto [nextId, cost] : reverseGraph[curId])
        {
            // std::cout << "insert : " << curId << " to " << nextId << "\n";
            isInShortestPath[nextId][curId] = true;
            if (!visited2[nextId])
            {
                visited2[nextId] = true;
                idQueue.emplace(nextId);
            }
        }
    }
}

int main()
{
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios::sync_with_stdio(false);
    while (true)
    {
        std::cin >> numLocations >> numRoads;
        if (numLocations == 0 && numRoads == 0)
            break;
        std::cin >> begin >> end;

        graph.clear();
        reverseGraph.clear();

        graph.resize(numLocations);
        reverseGraph.resize(numLocations);

        for (int i = 0; i < numLocations; ++i)
        {
            visited[i] = false;
            visited2[i] = false;
            minCost[i] = std::numeric_limits<int>::max();
            for (int j = 0; j < numLocations; ++j)
                isInShortestPath[i][j] = false;
        }

        for (int i = 0; i < numRoads; ++i)
        {
            int from, to, cost;
            std::cin >> from >> to >> cost;
            graph[from].emplace_back(std::make_pair(to, cost));
            // reverseGraph[to].emplace_back(std::make_pair(from, cost));
        }

        dijkstra(begin, end);
        logShortestPath(end, begin);

        for (int i = 0; i < numLocations; ++i)
        {
            visited[i] = false;
            minCost[i] = std::numeric_limits<int>::max();
        }

        dijkstra(begin, end);

        if (minCost[end] == std::numeric_limits<int>::max())
            std::cout << "-1\n";
        else
            std::cout << minCost[end] << "\n";
    }

    return 0;
}