#include <bits/stdc++.h>

using namespace std;

void restore_permutation(vector<int>& elements) {
    unordered_set<int> set;
    for (const auto& element : elements) {
        if (set.find(elements[element]) != set.end())  // check if element is in the set
            continue;
        cout << elements[element] << ' ';
        set.insert(elements[element]);
    }
    cout << '\n';
}

int main() {
    size_t numTestCases;
    cin >> numTestCases;

    while (numTestCases--) {
        int permutationSize;
        cin >> permutationSize;

        vector<int> elements(2 * permutationSize);
        for (auto& element : elements)
            cin >> element;

        restore_permutation(elements);
    }
}