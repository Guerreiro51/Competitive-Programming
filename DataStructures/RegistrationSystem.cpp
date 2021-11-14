#include <bits/stdc++.h>

using namespace std;

int main() {
    size_t numberOfUsers;
    cin >> numberOfUsers;

    unordered_map<string, int> users;
    while (numberOfUsers--) {
        string user;
        cin >> user;
        if (users.find(user) == users.end()) {  // If the user is not registered
            cout << "OK\n";
            users[user] = 1;
        } else
            cout << user << users[user]++ << '\n';
    }

    return 0;
}