#include <bits/stdc++.h>

using namespace std;

int main() {
    string inputStr;
    cin >> inputStr;

    deque<char> outStr;
    outStr.push_front(inputStr[0]);

    for (auto strIt = inputStr.begin() + 1; strIt != inputStr.end(); strIt++) {
        if (outStr.back() == *strIt)
            outStr.pop_back();  // if its equal, remove both (iterator moves and last character is popped)
        else
            outStr.push_back(*strIt);  // not equal, push
    }

    for (auto& c : outStr)
        cout << c;

    return 0;
}