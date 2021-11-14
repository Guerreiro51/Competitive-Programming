#include <bits/stdc++.h>

constexpr size_t MAXITERATION = 50UL;

using namespace std;

// looks for a root using binary search, receives the function and it's derivative
double findRoots(const function<double(double)>& func, const function<double(double)>& dfunc, double left, double right) {
    double x;
    for (size_t i = 0; i < MAXITERATION; i++) {
        x = (left + right) / 2.0;

        if(func(x)*dfunc(x) >= 0.0)
            right = x;
        else
            left = x;
    }
    x = (left + right) / 2.0;
    if (abs(func(x)) <= 1e-7)  // if there is a root
        return x;
    else
        return -1;
}

int main() {
    cout << std::fixed;
    cout << std::setprecision(4);  // Rounding to 4 decimal places

    double p, q, r, s, t, u;
    while (cin >> p >> q >> r >> s >> t >> u) {
        auto func = [&](double x) {
            return (p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u);
        };

        auto dfunc = [=](double x) {
            double cosx = cos(x);
            return (-p * exp(-x) + q * cosx - r * sin(x) + 1 / (cosx * cosx) + 2 * t * x);
        };

        double x = findRoots(func, dfunc, 0.0, 1.0);
        if (x == -1)
            cout << "No solution" << endl;
        else
            cout << x << endl;
    }
    return 0;
}