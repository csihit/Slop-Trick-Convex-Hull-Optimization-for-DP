#include <iostream>
#include <vector>
#include <limits>
using namespace std;

typedef long long ll;

struct Line {
    ll m, c;
    Line(ll _m, ll _c) : m(_m), c(_c) {}

    ll eval(ll x) const {
        return m * x + c;
    }
};

class ConvexHull {
    vector<Line> hull;

    // Check if line2 is unnecessary
    bool isBad(const Line& line1, const Line& line2, const Line& line3) {
        return (line3.c - line1.c) * (line1.m - line2.m) <= (line2.c - line1.c) * (line1.m - line3.m);
    }

public:
    void addLine(ll m, ll c) {
        Line newLine(m, c);
        while (hull.size() >= 2 &&
               isBad(hull[hull.size() - 2], hull[hull.size() - 1], newLine)) {
            hull.pop_back();
        }
        hull.push_back(newLine);
    }

    ll query(ll x) {
        int l = 0, r = hull.size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (hull[mid].eval(x) <= hull[mid + 1].eval(x))
                r = mid;
            else
                l = mid + 1;
        }
        return hull[l].eval(x);
    }
};

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<ll> a(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    vector<ll> dp(n);
    dp[0] = 0;

    ConvexHull cht;
    cht.addLine(-2 * a[0], dp[0] + a[0] * a[0]);

    for (int i = 1; i < n; ++i) {
        dp[i] = a[i] * a[i] + cht.query(a[i]);
        cht.addLine(-2 * a[i], dp[i] + a[i] * a[i]);
    }

    cout << "Minimum cost dp[n] = " << dp[n - 1] << endl;
    return 0;
}
