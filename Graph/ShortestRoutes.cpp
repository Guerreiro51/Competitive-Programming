#include <bits/stdc++.h>

using namespace std;

using Connection = pair<size_t, size_t>;  // first is the distance, second is the destination
using AdjList = vector<Connection>;
using Graph = vector<AdjList>;

void findShortestPathDijkstra(const Graph& g, size_t beginning) {
    vector<size_t> minDist(g.size(), ULONG_MAX);

    priority_queue<Connection, vector<Connection>, greater<Connection>> qRoutes;
    qRoutes.emplace(0, beginning);
    minDist[beginning] = 0;

    while (!qRoutes.empty()) {
        Connection nextConnection = qRoutes.top();
        qRoutes.pop();
        size_t from = nextConnection.second;
        for (const auto& to : g[from]) {
            size_t dist = nextConnection.first + to.first;
            if (dist < minDist[to.second]) {  // This is here to prevent unlimited iterations
                minDist[to.second] = dist;
                qRoutes.emplace(dist, to.second);
            }
        }
    }

    for (size_t i = 0; i < minDist.size(); i++)
        cout << minDist[i] << " ";
    cout << '\n';
}

int main() {
    size_t numberOfCities, numberOfConnections;
    cin >> numberOfCities >> numberOfConnections;

    Graph flightConnections(numberOfCities);
    for (size_t i = 0; i < numberOfConnections; i++) {
        size_t from, to, distance;
        cin >> from >> to >> distance;
        flightConnections[--from].emplace_back(distance, --to);  // -- to make it a 0-indexed list
    }

    findShortestPathDijkstra(flightConnections, 0);

    return 0;
}