#include <bits/stdc++.h>

using namespace std;

using Connection = pair<size_t, size_t>;  // first is the destination, second is the distance
using AdjList = vector<Connection>;
using Graph = vector<AdjList>;

void findShortestPath(const Graph& g, int from, int dest) {
    vector<unsigned> minDist(g.size(), UINT_MAX);
    bool possible = false;

    queue<Connection> qConnection;
    qConnection.emplace(from, 1);  // for some reason, we need to start with distance 1 instead of 0
    minDist[from] = 1;

    vector<size_t> parent(g.size(), -1);
    while (!qConnection.empty()) {
        Connection nextConnection = qConnection.front();
        qConnection.pop();
        int from = nextConnection.first;
        if (from != dest)
            // BFS
            for (const auto& to : g[from]) {
                unsigned int dist = nextConnection.second + to.second;
                if (dist < minDist[to.first]) {
                    minDist[to.first] = dist;
                    qConnection.emplace(to.first, dist);
                    parent[to.first] = from;
                }
            }
        else
            possible = true;
    }

    if (possible) {
        // recreate the sequence using the parent vector
        vector<size_t> sequence(minDist[dest]);
        sequence[minDist[dest] - 1] = dest;
        for (int i = minDist[dest] - 2; i >= 0; i--)
            sequence[i] = parent[sequence[i + 1]];

        cout << sequence.size() << '\n';
        for (size_t i = 0; i < sequence.size() - 1; i++)
            cout << sequence[i] + 1 << ' ';
        cout << sequence.back() + 1 << '\n';
    } else
        cout << "IMPOSSIBLE\n";
}

int main() {
    size_t numberOfComputers, numberOfConnections;
    cin >> numberOfComputers >> numberOfConnections;

    Graph network(numberOfComputers);

    for (size_t i = 0; i < numberOfConnections; i++) {
        size_t from, to;
        cin >> from >> to;

        // make it a 0-indexed list
        from--;
        to--;

        network[from].emplace_back(to, 1);
        network[to].emplace_back(from, 1);
    }

    findShortestPath(network, 0, numberOfComputers - 1);

    return 0;
}