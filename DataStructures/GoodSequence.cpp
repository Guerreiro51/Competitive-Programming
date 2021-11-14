#include <bits/stdc++.h>

using namespace std;

int main() {
    size_t sequenceSize;
    cin >> sequenceSize;

    unordered_map<int, int> sequence;
    while (sequenceSize--) {
        int number;
        cin >> number;
        if (sequence.find(number) != sequence.end())
            sequence[number]++;
        else
            sequence[number] = 1;
    }

    int retval = 0;
    for (auto elem : sequence) {
        int remove = elem.second - elem.first;
        if (remove < 0)             // we would need to add
            retval += elem.second;  // therefore remove all
        else
            retval += remove;
    }

    cout << retval << '\n';
}