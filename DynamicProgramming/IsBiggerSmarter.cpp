#include <bits/stdc++.h>

using namespace std;

struct Elephant {
    int weight, iq, id;

    Elephant(int pWeight, int pIQ, int pID) : weight(pWeight), iq(pIQ), id(pID) {}

    friend bool operator>(const Elephant& a, const Elephant& b) {
        if (a.weight == b.weight) return a.iq > b.iq;
        return a.weight > b.weight;
    }
};

// Calculates the length of the longest sequence of elefants that are increasingly skinnier and smarter using dynamic programming approach.
void longestSkinnySmartElephantsSequence(const vector<Elephant>& elephants) {
    vector<int> sequenceSizeDP(elephants.size());
    vector<size_t> parent(elephants.size(), -1);

    for (int i = 0; i < (int)elephants.size(); i++) {  // for every subset of 0..i elephants where the ith elephant is included
        sequenceSizeDP[i] = 1;
        parent[i] = i;
        for (int j = i - 1; j >= 0; j--)                                                         // for every elephant before the last one
            if (elephants[j].weight > elephants[i].weight && elephants[j].iq < elephants[i].iq)  // check if including it or not is possible
                if (sequenceSizeDP[i] < sequenceSizeDP[j] + 1) {
                    parent[i] = j;
                    sequenceSizeDP[i] = sequenceSizeDP[j] + 1;  // Calculate the maximum sequence including or not including elephant j and get the longest one
                }
    }

    // the longest sequence might not include the last elephant, so we need to find the max_element
    size_t maxPos = max_element(sequenceSizeDP.begin(), sequenceSizeDP.end()) - sequenceSizeDP.begin();
    cout << sequenceSizeDP[maxPos] << '\n';

    // recreate the sequence using the parent vector
    vector<size_t> sequence(sequenceSizeDP[maxPos]);
    sequence[0] = maxPos;
    for (size_t i = 1; i < sequence.size(); i++)
        sequence[i] = parent[sequence[i - 1]];

    // show the elephant's id
    for (const auto& eleph : sequence)
        cout << elephants[eleph].id << '\n';
}

int main() {
    vector<Elephant> elephants;

    int weight, iq, id = 1;
    while (cin >> weight && cin >> iq)
        elephants.emplace_back(weight, iq, id++);

    sort(elephants.begin(), elephants.end(), greater<Elephant>());
    longestSkinnySmartElephantsSequence(elephants);

    return 0;
}