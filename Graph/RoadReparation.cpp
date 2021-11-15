#include <bits/stdc++.h>

using namespace std;

class UnionFind {
 private:
    std::vector<size_t> parent;
    std::vector<size_t> rank;

 public:
    UnionFind(const size_t& size) : parent(size), rank(size, 0) {
        for (size_t i = 0; i < parent.size(); i++)
            parent[i] = i;  // initially, everybody is its own father
    }

    size_t findSet(const size_t& i) {
        if (parent[i] == i)
            return i;
        return findSet(parent[i]);
    }

    bool isSameSet(const size_t& i, const size_t& j) {
        return (findSet(i) == findSet(j));
    }

    void unionSet(const size_t& i, const size_t& j) {
        size_t x = findSet(i);
        size_t y = findSet(j);

        // Creates a balanced heap to represent the combined set
        if (x != y) {
            if (rank[x] > rank[y])
                parent[y] = x;
            else {
                parent[x] = y;
                if (rank[x] == rank[y])
                    rank[y]++;
            }
        }
    }
};

struct Edge {
    int64_t weight;
    size_t from;
    size_t to;

    Edge(const int64_t& pWeight, const size_t& pFrom, const size_t& pTo) : weight(pWeight), from(pFrom), to(pTo) {}
    Edge() = default;
    friend bool operator<(const Edge& i1, const Edge& i2) {
        return (i1.weight < i2.weight);  // We only care about the weight
    }
};

using AdjList = vector<Edge>;
using Graph = vector<AdjList>;

int64_t kruskal(const AdjList& connections, size_t numberOfVertices) {
    int64_t totalWeight = 0;
    UnionFind uf(numberOfVertices);

    // Finds the lowest weight path
    for (const auto& connection : connections) {
        if (!uf.isSameSet(connection.from, connection.to)) {
            totalWeight += connection.weight;
            uf.unionSet(connection.from, connection.to);
        }
    }

    // Check if it is all connected
    size_t set = uf.findSet(0);
    for (size_t i = 1; i < numberOfVertices; i++) {
        if (set != uf.findSet(i)) {
            return -1;
        }
    }

    return totalWeight;
}

int main() {
    size_t numberOfCities, numberOfRoads;
    cin >> numberOfCities >> numberOfRoads;

    AdjList roads(numberOfRoads);
    for (auto& road : roads) {
        cin >> road.from >> road.to >> road.weight;
        road.from--;
        road.to--;
    }
    sort(roads.begin(), roads.end());

    auto reparationCost = kruskal(roads, numberOfCities);
    if (reparationCost != -1)
        cout << reparationCost << '\n';
    else
        cout << "IMPOSSIBLE\n";

    return 0;
}
