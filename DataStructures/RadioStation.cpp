#include <bits/stdc++.h>

using namespace std;

int main() {
    size_t ipAmmount, cmdAmmount;
    cin >> ipAmmount >> cmdAmmount;

    unordered_map<string, string> ipToName;
    for (size_t i = 0; i < ipAmmount; i++) {
        string name, ip;
        cin >> name >> ip;
        ipToName[ip] = name;
    }

    for (size_t i = 0; i < cmdAmmount; i++) {
        string cmd, ip;
        cin >> cmd >> ip;
        ip.pop_back();  // drop the ';' at the end

        cout << cmd << " " << ip << "; #" << ipToName[ip] << '\n';
    }

    return 0;
}