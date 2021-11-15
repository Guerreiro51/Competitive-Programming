#include <bits/stdc++.h>

using namespace std;

using Connection = pair<size_t, size_t>;  // first is the distance, second is the destination
using AdjList = vector<Connection>;
using Graph = vector<AdjList>;

struct Option {
    int64_t cost;
    size_t dest;
    bool discountUsed;
    Option(const int64_t& pCost, const size_t& pDest, const bool& pDiscountUsed)
        : cost(pCost), dest(pDest), discountUsed(pDiscountUsed) {}
    friend bool operator>(const Option& a, const Option& b) {
        if(a.cost == b.cost) return a.dest > b.dest;
        return a.cost > b.cost;
    }
};

int64_t findCheapestPathDijkstra(const Graph& g, size_t beginning, size_t dest) {
    vector<int64_t> minCost(g.size(), INT64_MAX);          // The minimum cost without using discount
    vector<int64_t> minCostDiscount(g.size(), INT64_MAX);  // The minimum cost using discount

    priority_queue<Option, vector<Option>, greater<Option>> qRoutes;
    qRoutes.emplace(0, beginning, false);
    minCost[beginning] = 0;
    minCostDiscount[beginning] = 0;

    while (!qRoutes.empty()) {
        Option nextOption = qRoutes.top();
        qRoutes.pop();

        size_t from = nextOption.dest;
        if (nextOption.discountUsed) {                    // if discount was already used
            if (minCostDiscount[from] < nextOption.cost)  // and there's a better route with discount already
                continue;                                  // skip
        } else {                                           // if discount was not used yet
            if (minCost[from] < nextOption.cost)          // and there's a better route without using discount aswell
                continue;                                  // skip
        }

        for (const auto& to : g[from]) {
            if (nextOption.discountUsed) {  // if discount was already used
                int64_t costDiscount = nextOption.cost + to.first;
                if (costDiscount < minCostDiscount[to.second]) {
                    minCostDiscount[to.second] = costDiscount;
                    qRoutes.emplace(costDiscount, to.second, true);
                }
            } else {
                int64_t cost = nextOption.cost + to.first;
                if (cost < minCost[to.second]) {
                    minCost[to.second] = cost;
                    qRoutes.emplace(cost, to.second, false);  // don't use discount
                }
                int64_t costDiscount = nextOption.cost + to.first / 2;
                if (costDiscount < minCostDiscount[to.second]) {
                    minCostDiscount[to.second] = costDiscount;
                    qRoutes.emplace(costDiscount, to.second, true);  // use discount
                }
            }
        }
    }

    return minCostDiscount[dest];
}

int main() {
    size_t numberOfCities, numberOfConnections;
    cin >> numberOfCities >> numberOfConnections;

    Graph flightConnections(numberOfCities);

    for (size_t i = 0; i < numberOfConnections; i++) {
        size_t from, to, distance;
        cin >> from >> to >> distance;
        flightConnections[--from].emplace_back(distance, --to); // -- to make it a 0-indexed list
    }

    cout << findCheapestPathDijkstra(flightConnections, 0, numberOfCities - 1) << '\n';

    return 0;
}