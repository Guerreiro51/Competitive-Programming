#include <bits/stdc++.h>

using namespace std;

struct Crewmate {
    std::string name;
    std::string role;
    int roleWeight;
    int arrivalOrder;  // The order of arrival, used as tiebreaking if the weight is equal
    Crewmate(const string& pName, const string& pRole, int pRoleWeight, int pArrival)
        : name(pName), role(pRole), roleWeight(pRoleWeight), arrivalOrder(pArrival) {}

    static bool Compare(const Crewmate& a, const Crewmate& b) {
        if (a.roleWeight == b.roleWeight) return (a.arrivalOrder > b.arrivalOrder);
        return (a.roleWeight < b.roleWeight);
    }
};

using CrewmatePQ = priority_queue<Crewmate, std::vector<Crewmate>, decltype(Crewmate::Compare)*>;

int main() {
    unordered_map<string, int> roleWeight;
    roleWeight["rat"] = 1000;
    roleWeight["woman"] = 100;
    roleWeight["child"] = 100;
    roleWeight["man"] = 10;
    roleWeight["captain"] = 1;

    size_t crewSize;
    cin >> crewSize;

    CrewmatePQ exitQueue(Crewmate::Compare);
    for (size_t i = 1; i <= crewSize; i++) {
        string crewmateName, crewmateRole;
        cin >> crewmateName >> crewmateRole;
        exitQueue.emplace(crewmateName, crewmateRole, roleWeight[crewmateRole], i);
    }

    while (!exitQueue.empty()) {
        cout << exitQueue.top().name << '\n';  // Shows the current first crewmate in the Queue
        exitQueue.pop();                       // 'Rescues' the first crewmate in the queue
    }

    return 0;
}