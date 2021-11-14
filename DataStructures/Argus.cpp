#include <bits/stdc++.h>

using namespace std;

struct Query {
    int num;
    int period;
    int lastActivation;
    Query(const int& pNum, const int& pPeriod)
        : num(pNum), period(pPeriod), lastActivation(pPeriod){};

    static bool Compare(const Query& a, const Query& b) {
        if (a.lastActivation == b.lastActivation) return (a.num > b.num);
        return (a.lastActivation > b.lastActivation);
    }
};

using CrewmatePQ = priority_queue<Query, std::vector<Query>, decltype(Query::Compare)*>;

void solve(CrewmatePQ& pq, size_t numberOfQueriesToPrint) {
    for (size_t printedAmmount = 0; printedAmmount < numberOfQueriesToPrint; printedAmmount++) {
        Query currentQuery = pq.top();
        pq.pop();
        cout << currentQuery.num << '\n';

        // Update the query and put it back in the queue
        currentQuery.lastActivation += currentQuery.period;
        pq.push(currentQuery);
    }
}

int main() {
    CrewmatePQ queries(Query::Compare);

    while (true) {
        string registerInstruction;
        cin >> registerInstruction;
        if (registerInstruction == "#")
            break;

        int num, period;
        cin >> num >> period;
        queries.emplace(num, period);
    }

    size_t numberOfQueriesToPrint;
    cin >> numberOfQueriesToPrint;

    solve(queries, numberOfQueriesToPrint);

    return 0;
}