#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>

#define INF 1000000000

// visited array in [id][cost]
int minDist[101][10001];

int numAirports, money, numTickets;

struct Point
{
    int Id;
    int Cost;
    int Dist;
};

struct Compare
{
    bool operator()(Point lhs, Point rhs)
    {
        return lhs.Dist > rhs.Dist;
    }
};

// id, taken cost

bool dijkstra(const std::vector<std::deque<std::tuple<int, int, int>>> &airports)
{
    std::priority_queue<Point, std::vector<Point>, Compare>
        queue;

    queue.emplace(Point{1, 0, 0});
    minDist[1][0] = 0;

    while (!queue.empty())
    {
        auto curPoint = queue.top();
        auto from = curPoint.Id;
        auto curCost = curPoint.Cost;
        auto curDist = curPoint.Dist;
        queue.pop();

        if (from == numAirports)
            return true;

        if (minDist[from][curCost] < curDist)
            continue;

        for (const auto &[to, cost, dist] : airports[from])
        {
            auto nextCost = curCost + cost;
            auto nextDist = curDist + dist;
            if (nextCost > money)
                continue;

            if (minDist[to][nextCost] > nextDist)
            {
                for (int i = nextCost; i <= money; ++i)
                {
                    if (minDist[to][i] > nextDist)
                        minDist[to][i] = nextDist;
                    else
                        break;
                }
                queue.push(Point{to, nextCost, nextDist});
            }
        }
    }
    return false;
}

int main()
{
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios::sync_with_stdio(false);
    int testCases;
    std::cin >> testCases;
    std::vector<std::deque<std::tuple<int, int, int>>> airports;

    for (int testIdx = 0; testIdx < testCases; ++testIdx)
    {
        std::cin >> numAirports >> money >> numTickets;
        airports.clear();
        airports.resize(numAirports + 1);

        for (int i = 0; i < numTickets; ++i)
        {
            int from, to, cost, time;
            std::cin >> from >> to >> cost >> time;
            airports[from].push_back(std::make_tuple(to, cost, time));
        }

        for (int i = 1; i <= numAirports; ++i)
        {
            for (int j = 1; j <= money; ++j)
            {
                minDist[i][j] = INF;
            }
        }

        if (dijkstra(airports))
        {
            std::cout << minDist[numAirports][money] << "\n";
        }
        else
        {
            std::cout << "Poor KCM\n";
        }
    }
    return 0;
}
