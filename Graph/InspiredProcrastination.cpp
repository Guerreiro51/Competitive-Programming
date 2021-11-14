#include <bits/stdc++.h>

using namespace std;

struct Edge {
    size_t from, to;
    long weight;
};

bool bellmanFord(const vector<Edge>& edges, size_t numberOfVertices, vector<long>& distances) {
    distances.assign(numberOfVertices, LONG_MAX);  // starts everyone with infinity
    distances[0] = 0;

    // For every vertice in the graph, run through every edge and relax the distance if possible
    for (size_t v = 0; v < numberOfVertices; v++) {
        for (const Edge& edge : edges) {
            if (distances[edge.from] == LONG_MAX) continue;  // prevent overflow
            if (distances[edge.to] > distances[edge.from] + edge.weight) {
                distances[edge.to] = distances[edge.from] + edge.weight;
            }
        }
    }

    // Run the algorithm again, if it is possible to relax again, then there's a negative cycle.
    for (size_t v = 0; v < numberOfVertices; v++) {
        for (const Edge& edge : edges) {
            if (distances[edge.from] == LONG_MAX) continue;  // prevent overflow

            if (distances[edge.to] > distances[edge.from] + edge.weight) {
                return true;  // negative cycle found
            }
        }
    }

    return false;  // No negative cycle found
}
int main() {
    while (true) {
        size_t numberOfLifePoints, numberOfDecisions;
        cin >> numberOfLifePoints >> numberOfDecisions;

        if (numberOfLifePoints == 0 && numberOfDecisions == 0)
            return 0;

        vector<Edge> lifeDecisions(numberOfDecisions);
        while (numberOfDecisions--) {
            Edge edge;
            cin >> edge.from >> edge.to >> edge.weight;
            edge.from--;
            edge.to--;          // making it a 0-indexed list
            edge.weight *= -1;  // since we want to maximize

            lifeDecisions.emplace_back(edge);
        }
        vector<long> distances;
        bool infiniteDistance = bellmanFord(lifeDecisions, numberOfLifePoints, distances);

        if (infiniteDistance)
            cout << "Unlimited!\n";
        else
            cout << *min_element(distances.begin(), distances.end()) * -1 << '\n';

        lifeDecisions.clear();
    }
}