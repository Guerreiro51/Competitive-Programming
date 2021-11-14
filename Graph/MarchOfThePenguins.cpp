#include <bits/stdc++.h>
using namespace std;

constexpr long INF = LONG_MAX / 10;

struct EdmondsKarp {
    size_t numberOfNodes;
    vector<vector<long>> graph;
    vector<vector<size_t>> adj;

    EdmondsKarp(size_t n) : numberOfNodes(n), graph(n, vector<long>(n)), adj(n) {}

    void add_edge(size_t u, size_t v, long w) {
        graph[u][v] = w;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void remove_edge(size_t u, size_t v) {
        graph[u][v] = 0;
        adj[u].erase((find(adj[u].rbegin(), adj[u].rend(), v) + 1).base());
        adj[v].erase((find(adj[v].rbegin(), adj[v].rend(), u) + 1).base());
    }

    // finds a path in parent and returns the maximum flow through that path
    long bfs(size_t source, size_t sink, vector<long>& parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[source] = -2;  // just marking as visited

        queue<pair<size_t, long>> nextNode;
        nextNode.emplace(source, INF);
        while (!nextNode.empty()) {
            size_t from = nextNode.front().first;
            long capacity = nextNode.front().second;
            nextNode.pop();
            for (size_t to : adj[from]) {
                if (parent[to] == -1 && graph[from][to]) {
                    parent[to] = from;
                    capacity = min(capacity, graph[from][to]);
                    if (to == sink)
                        return capacity;

                    nextNode.emplace(to, capacity);
                }
            }
        }

        return 0;  // no path found
    }

    long flow(size_t source, size_t sink) {
        vector<long> parent(numberOfNodes);
        auto graphCopy = graph;

        long flow = 0L;
        while (long capacity = bfs(source, sink, parent)) {
            flow += capacity;
            for (size_t to = sink; to != source; to = parent[to]) {
                size_t from = parent[to];
                graph[from][to] -= capacity;  // forward edge
                graph[to][from] += capacity;  // backward edge
            }
        }
        graph = graphCopy;
        return flow;
    }

    void clear() {
        for (size_t i = 0; i < numberOfNodes; i++) {
            graph[i].clear();
            adj[i].clear();
        }
        graph.clear();
        adj.clear();
    }
};

int main() {
    size_t numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        size_t numberOfIcePieces;
        double maxJumpDistance;
        cin >> numberOfIcePieces >> maxJumpDistance;

        // (0~numberOfIcePieces-1) -> real ice pieces
        // (numberOfIcePieces ~ 2*numberOfIcePieces - 1) -> virtual ice pieces => models the number of jumps allowed in each ice piece
        // (2*numberOfIcePieces) -> virtual source of all penguins => models the initial number of penguins in each ice piece
        EdmondsKarp penguins(2 * numberOfIcePieces + 2);

        vector<pair<double, double>> position(numberOfIcePieces);
        vector<long> numberOfPenguins(numberOfIcePieces);
        vector<long> numberOfJumps(numberOfIcePieces);
        long totalNumberOfPenguins = 0;
        for (size_t i = 0; i < numberOfIcePieces; i++) {
            cin >> position[i].first >> position[i].second >> numberOfPenguins[i] >> numberOfJumps[i];

            // from the virtual ice pieces to the real ice pieces
            penguins.add_edge(i + numberOfIcePieces, i, numberOfJumps[i]);

            // from the virtual source to the virtual ice pieces
            penguins.add_edge(2 * numberOfIcePieces, i + numberOfIcePieces, numberOfPenguins[i]);

            totalNumberOfPenguins += numberOfPenguins[i];
        }
        penguins.add_edge(2 * numberOfIcePieces + 1, 2 * numberOfIcePieces, totalNumberOfPenguins);  // limit the totalNumberOfPenguins

        vector<vector<double>> distance(numberOfIcePieces, vector<double>(numberOfIcePieces));
        for (size_t i = 0; i < numberOfIcePieces; i++) {
            for (size_t j = i + 1; j < numberOfIcePieces; j++) {
                double x = position[i].first - position[j].first;
                double y = position[i].second - position[j].second;
                distance[i][j] = hypot(x, y);
                distance[j][i] = distance[i][j];

                // from the REAL ice pieces to every other virtual ice piece (if it's close enough)
                // when these paths are used, we spend the durability of the ice piece
                if (distance[i][j] <= maxJumpDistance) {
                    penguins.add_edge(i, j + numberOfIcePieces, INF);
                    penguins.add_edge(j, i + numberOfIcePieces, INF);
                }
            }
            distance[i][i] = 0.0;  // just for completude
        }

        bool noAnswer = true;
        for (size_t sink = 0; sink < numberOfIcePieces; sink++) {
            // Creates a passage from every ice piece to the sink (if it's close enough)
            // from the REAL ice pieces to every other REAL ice piece
            // when these paths are used, we DON'T spend the durability of the ice piece
            for (size_t source = 0; source < numberOfIcePieces; source++) {
                if (source == sink) continue;

                if (distance[source][sink] <= maxJumpDistance)
                    penguins.add_edge(source, sink, INF);
            }
            // Penguins born within the island shouldn't count
            penguins.graph[sink + numberOfIcePieces][sink] += numberOfPenguins[sink];

            long numberOfPenguinsThatCanReach = penguins.flow(2 * numberOfIcePieces + 1, sink);
            if (numberOfPenguinsThatCanReach == totalNumberOfPenguins) {
                if (noAnswer)
                    noAnswer = false;
                else
                    cout << ' ';
                cout << sink;
            }

            // Destroy every passage created previously
            penguins.graph[sink + numberOfIcePieces][sink] -= numberOfPenguins[sink];
            for (long source = numberOfIcePieces - 1; source >= 0; source--) {
                if (source == long(sink)) continue;

                if (distance[source][sink] <= maxJumpDistance)
                    penguins.remove_edge(source, sink);
            }
        }
        if (noAnswer)
            cout << -1;
        cout << '\n';
    }
    return 0;
}