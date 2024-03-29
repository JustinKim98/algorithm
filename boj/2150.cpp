#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

std::deque<std::priority_queue<int, std::vector<int>, std::greater<>>> sccs;
std::deque<int> stack;
std::vector<bool> done;

int minCnt = 0;

int tarjan(int index, const std::vector<std::deque<int>> &vertices, std::vector<int> &min, std::vector<bool> &done)
{
    minCnt += 1;
    auto curMin = minCnt;
    auto childMin = curMin;
    min[index] = curMin;

    stack.emplace_back(index);
    for (auto childIdx : vertices[index])
    {
        if (done[childIdx])
            continue;

        if (min[childIdx])
            childMin = std::min(childMin, min[childIdx]);
        else
            childMin = std::min(childMin, tarjan(childIdx, vertices, min, done));
    }

    if (curMin == childMin)
    {
        std::priority_queue<int, std::vector<int>, std::greater<>>
            scc;
        while (stack.back() != index)
        {
            scc.emplace(stack.back());
            done[stack.back()] = true;
            stack.pop_back();
        }
        scc.emplace(stack.back());
        done[stack.back()] = true;
        stack.pop_back();
        sccs.emplace_back(scc);
    }

    // std::cout << "childMin : " << childMin << "\n";
    return childMin;
}

int main()
{
    int numVertices;
    int numEdges;
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    std::cin >> numVertices >> numEdges;
    std::vector<std::deque<int>> vertices(numVertices, std::deque<int>());
    std::vector<bool> done(numVertices, false);
    std::vector<int> min(numVertices, 0);

    for (int i = 0; i < numEdges; ++i)
    {
        int parentId, childId;
        std::cin >> parentId >> childId;
        vertices[parentId - 1].emplace_back(childId - 1);
    }

    for (int i = 0; i < numVertices; ++i)
        if (!min[i])
            tarjan(i, vertices, min, done);

    std::sort(sccs.begin(), sccs.end(), [](auto &l, auto &r)
              { return l.top() < r.top(); });

    std::cout << sccs.size() << "\n";
    for (auto &scc : sccs)
    {
        while (!scc.empty())
        {
            std::cout << scc.top() + 1 << " ";
            scc.pop();
        }
        std::cout << "-1\n";
    }

    return 0;
}
