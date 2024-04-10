#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_set>

bool done[20001];
int minCnt[20001];
int sccId[200001];
int cnt = 0;
int numVars, numTokens;

std::deque<int> stack;
std::deque<std::unordered_set<int>> sccs;
// id = given + 10000;
std::unordered_map<int, std::unordered_set<int>> graph;
std::vector<bool> sccState;

inline int getOriginId(int id)
{
    return id - 10000;
}

inline int getStoreId(int id)
{
    return id + 10000;
}

inline bool negative(int id)
{
    return id < 10000;
}

inline int getVarId(int id)
{
    return std::abs(getOriginId(id));
}

int tarjan(int id)
{
    cnt += 1;
    const int curCnt = cnt;
    minCnt[id] = curCnt;
    int childMin = minCnt[id];
    stack.emplace_back(id);

    for (auto childId : graph[id])
    {
        if (done[childId])
            continue;

        if (minCnt[childId] > 0)
        {
            childMin = std::min(childMin, minCnt[childId]);
        }
        else
        {
            childMin = std::min(childMin, tarjan(childId));
        }
    }

    if (childMin == curCnt)
    {
        std::unordered_set<int> scc;
        while (true)
        {
            auto poppedId = stack.back();
            stack.pop_back();
            scc.emplace(poppedId);
            sccId[poppedId] = sccs.size();
            done[poppedId] = true;
            if (poppedId == id)
                break;
        }
        sccs.emplace_back(scc);
    }

    return childMin;
}

bool hasSolution()
{
    for (const auto &scc : sccs)
    {
        // std::cout << "scc\n";
        for (auto id : scc)
        {
            // std::cout << "id : " << id << "\n";
            if (negative(id) && scc.find(getStoreId(-getOriginId(id))) != scc.end())
                return false;
        }
    }
    return true;
}

int sign[10001];

void getSequence()
{
    // std::cout << "size : " << sccs.size() << "\n";
    for (int i = sccs.size() - 1; i >= 0; --i)
    {
        bool curSign = sccState[i];

        if (!curSign)
        {
            for (auto id : sccs[i])
            {
                curSign |= sign[getVarId(id)] == 1;
            }
        }
        else
        {
            for (auto id : sccs[i])
            {
                for (auto next : graph[id])
                {
                    if (sccId[next] != i)
                    {
                        // std::cout << "next : " << next << "\n";

                        sccState[sccId[next]] = true;
                    }
                }
            }
        }

        // std::cout << "curSign : " << curSign << "\n";

        int toStore = curSign ? 1 : -1;
        for (auto id : sccs[i])
        {
            // std::cout << "varId : " << getVarId(id) << " negative : " << id << " : " << negative(id) << "\n";
            sign[getVarId(id)] = negative(id) ? -toStore : toStore;
        }
    }
}

int main()
{
    std::cin >> numVars >> numTokens;

    for (int i = 0; i < numTokens; ++i)
    {
        int from, to;
        std::cin >> from >> to;
        graph[getStoreId(-from)].emplace(getStoreId(to));
        graph[getStoreId(-to)].emplace(getStoreId(from));
    }

    for (int i = 0; i <= 20000; ++i)
    {
        done[i] = false;
        minCnt[i] = 0;
    }

    for (int i = 0; i < 10000; ++i)
        sign[i] = 0;

    for (int i = 1; i <= numVars; ++i)
    {
        if (graph.find(getStoreId(i)) != graph.end() && !done[getStoreId(i)])
            tarjan(getStoreId(i));
    }

    for (int i = -numVars; i <= -1; ++i)
    {
        if (graph.find(getStoreId(i)) != graph.end() && !done[getStoreId(i)])
            tarjan(getStoreId(i));
    }

    if (!hasSolution())
    {
        std::cout << 0 << "\n";
        return 0;
    }

    std::cout << 1 << "\n";

    // sccState = std::vector<bool>(sccs.size(), false);
    // getSequence();
    // for (int i = 1; i <= numVars; ++i)
    //     printf("%d ", (sign[i] > 0 ? 1 : 0));
    // std::cout << (sign[i] > 0 ? 1 : 0) << " ";

    return 0;
}
