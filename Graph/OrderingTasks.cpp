#include <bits/stdc++.h>

#define MAX_TASK 100

using namespace std;

using AdjList = vector<uint32_t>;
using Graph = vector<AdjList>;

void dfs(Graph& graph, uint32_t startingVertice, bitset<MAX_TASK>& visited, deque<uint32_t>& topologicalOrder) {
    visited[startingVertice] = true;
    for (uint32_t vertice : graph[startingVertice])
        if (!visited[vertice])
            dfs(graph, vertice, visited, topologicalOrder);
    topologicalOrder.push_front(startingVertice);
}

void find_topologicalOrder(Graph& graph, uint32_t numberOfVertices) {
    bitset<MAX_TASK> visited;
    deque<uint32_t> topologicalOrder;
    for (uint32_t vertice = 0; vertice < numberOfVertices; vertice++)
        if (!visited[vertice])
            dfs(graph, vertice, visited, topologicalOrder);

    for (uint32_t vertice : topologicalOrder)
        cout << vertice + 1 << ' ';  // + 1 to restore the original 1-indexing
    cout << '\n';
}

int main() {
    uint32_t numberOfTasks, numberOfDirectPrecedences;
    Graph taskPredences(MAX_TASK);  //taskPredences[u] = {v, w, x}, means that 'u' must be done befone 'v', 'w' or 'x'

    while (true) {
        cin >> numberOfTasks >> numberOfDirectPrecedences;
        if (numberOfTasks == 0 && numberOfDirectPrecedences == 0) break;

        while (numberOfDirectPrecedences--) {
            uint32_t precedence, task;
            cin >> precedence >> task;

            taskPredences[--precedence].push_back(--task);  //using -- to make it a 0-indexed-array
        }

        find_topologicalOrder(taskPredences, numberOfTasks);

        while (--numberOfTasks)
            taskPredences[numberOfTasks].clear();
    }

    return 0;
}