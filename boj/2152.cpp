#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>
#include <limits>

int numCities, numPaths, start, end;

bool done[10001];
int minCnt[10001];
bool visited[10001];
bool sccVisited[10001];
int sccId[10001]; // Stores Id of the scc for each vertex
int minId = 0;
std::vector<std::deque<int>> graph;
std::vector<std::unordered_set<int>> sccGraph;

std::deque<int> stack;

std::deque<std::deque<int>> sccs;

int tarjan(int curId)
{
    minId += 1;
    minCnt[curId] = minId;
    visited[curId] = true;
    int curCnt = minId;
    int childMin = curCnt;
    stack.emplace_back(curId);

    for (auto nextId : graph[curId])
    {
        if (done[nextId])
            continue;

        if (visited[nextId])
        {
            childMin = std::min(childMin, minCnt[nextId]);
        }
        else
        {
            childMin = std::min(childMin, tarjan(nextId));
        }
    }

    if (childMin == curCnt)
    {
        std::deque<int> scc;
        int curSccId = sccs.size();
        while (true)
        {
            if (stack.back() == curId)
            {
                scc.emplace_back(curId);
                sccId[curId] = curSccId;
                done[curId] = true;
                stack.pop_back();
                break;
            }

            scc.emplace_back(stack.back());
            sccId[stack.back()] = curSccId;

            done[stack.back()] = true;
            stack.pop_back();
        }
        sccs.emplace_back(scc);
    }

    return childMin;
}

bool foundPath = false;
int findMaxPath(int curId, int endSccId)
{
    sccVisited[curId] = true;
    if (curId == endSccId)
    {
        // std::cout << "return : " << curId << " size : " << sccs[curId].size() << "\n";
        foundPath = true;
        return sccs[curId].size();
    }

    int maxVal = 0;
    for (auto nextSccId : sccGraph[curId])
    {
        if (!sccVisited[nextSccId])
            maxVal = std::max(maxVal, findMaxPath(nextSccId, endSccId));
    }

    return maxVal + sccs[curId].size();
}

int main()
{
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios::sync_with_stdio(false);

    std::cin >> numCities >> numPaths >> start >> end;
    graph.clear();
    graph.resize(numCities + 1);
    for (int i = 0; i <= numCities; ++i)
    {
        done[i] = false;
        minCnt[i] = std::numeric_limits<int>::max();
        visited[i] = false;
        sccVisited[i] = false;
        sccId[i] = -1;
    }

    for (int i = 0; i < numPaths; ++i)
    {
        int from, to;
        std::cin >> from >> to;
        graph[from].emplace_back(to);
    }

    tarjan(start);

    if (!done[end])
    {
        std::cout << 0 << "\n";
        return 0;
    }

    sccGraph.resize(sccs.size());

    std::vector<int> dp(sccs.size(), 0);

    dp[sccs.size() - 1] = sccs.back().size();
    for (int sccIdx = sccs.size() - 1; sccIdx >= 0; --sccIdx)
    {
        for (auto vertex : sccs[sccIdx])
        {
            for (auto next : graph[vertex])
            {
                if (sccId[next] != sccIdx)
                {
                    dp[sccId[next]] = std::max(dp[sccId[next]],
                                               dp[sccIdx] + static_cast<int>(sccs[sccId[next]].size()));
                }
            }
        }
    }

    // // Construct graph with SCCs
    // for (int curSccId = 0; curSccId < sccs.size(); ++curSccId)
    // {
    //     for (auto id : sccs[curSccId])
    //     {
    //         if (sccId[id] != curSccId)
    //         {
    //             sccGraph[curSccId].emplace(sccId[id]);
    //         }
    //     }
    // }

    // // Find path maximizing sum of vertices on path from beginSCC to endSCC inside DAG
    // int res = findMaxPath(sccId[start], sccId[end]);

    std::cout << dp[sccId[end]] << "\n";

    return 0;
}
