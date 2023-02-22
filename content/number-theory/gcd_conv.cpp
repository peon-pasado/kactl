#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 
 *      return d[i] = sum_{gcd(x, y) = i} a[x] * b[y]
 */

vector<int> gcd_conv(vector<int> a, vector<int> b) {
    int n = max(a.size(), b.size()) - 1;
    a.resize(n); b.resize(n);
    vector<int> d(n + 1);
    for (int i=0; p[i]<=n; ++i) {
        for (int j=n/p[i]; j>=1; --j) {
            a[j] += a[j * p[i]];	
            b[j] += b[j * p[i]];
        }
    }
    for (int i=1; i<=n; ++i) d[i] = a[i] * b[i];
    for (int i=0; p[i]<=n; ++i) {
        for (int j=1; j * p[i] <= n; ++j) {
            d[j] -= d[j * p[i]];
        }
    }
    return d;
} 