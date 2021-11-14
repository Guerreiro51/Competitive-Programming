#include <bits/stdc++.h>

#define MAXIMUM_NUMBER_OF_SCHOOL 100

using namespace std;

using adj = pair<size_t, size_t>;  // destination, weight
using AdjList = vector<adj>;
using Graph = vector<AdjList>;

struct Edge {
    size_t from, to, weight;
    bool used = false, removed = false;
};

bool cmp(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

class UnionFind {
 private:
    size_t parent[MAXIMUM_NUMBER_OF_SCHOOL];
    size_t unionSize[MAXIMUM_NUMBER_OF_SCHOOL];

 public:
    void init() {
        // everybody is its own Union
        for (size_t i = 0; i < MAXIMUM_NUMBER_OF_SCHOOL; i++) {
            parent[i] = i;
            unionSize[i] = 1;
        }
    }

    size_t find(const size_t& u) {
        if (parent[u] == u)
            return u;
        return find(parent[u]);
    }

    void merge(const size_t& u, const size_t& v) {
        size_t parentU = find(u), parentV = find(v);

        if (parentU == parentV) return;  // if they're already the same union

        if (unionSize[parentU] > unionSize[parentV]) swap(parentU, parentV);  // 'u' is the smaller union

        parent[parentU] = parentV;                 // connect u in v
        unionSize[parentV] += unionSize[parentU];  // update the unionSize
    }

    size_t kruskal(vector<Edge>& edges, const bool& firstTime, const size_t& numberOfVertices) {
        size_t retval = 0;  // weight of the minimum spanning tree

        if (firstTime) {  // extremely hardcoded. Gross
            for (Edge& edge : edges) {
                if (find(edge.from) != find(edge.to)) {
                    edge.used = true;  // only mark as used if its the first time
                    retval += edge.weight;
                    merge(edge.from, edge.to);
                }
            }
        } else {
            for (Edge& edge : edges) {
                if (edge.removed) continue;
                if (find(edge.from) != find(edge.to)) {
                    retval += edge.weight;
                    merge(edge.from, edge.to);
                }
            }
            if (unionSize[find(0)] != numberOfVertices)  // checking if every school is connected
                return ULONG_MAX;
        }

        return retval;
    }
};

int main() {
    unsigned numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        UnionFind connectedSchools;
        size_t numberOfSchools, numberOfConnections;
        cin >> numberOfSchools >> numberOfConnections;

        vector<Edge> connections(numberOfConnections);
        for (size_t i = 0; numberOfConnections--; i++) {
            Edge edge;
            cin >> edge.from >> edge.to >> edge.weight;
            edge.from--;
            edge.to--;  // making it a 0-indexed list

            connections[i] = edge;
        }
        sort(connections.begin(), connections.end(), cmp);

        connectedSchools.init();
        cout << connectedSchools.kruskal(connections, true, numberOfSchools) << ' ';

        size_t secondBest = ULONG_MAX;
        for (size_t i = 0; i < connections.size(); i++)
            if (connections[i].used) {
                connections[i].removed = true;

                connectedSchools.init();
                secondBest = min(secondBest, connectedSchools.kruskal(connections, false, numberOfSchools));

                connections[i].removed = false;
            }

        cout << secondBest << '\n';
    }

    return 0;
}