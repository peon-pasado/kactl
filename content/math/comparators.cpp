//0 <= a, c <= 1e9 and 0 <= b, d <= 1e18 
using ll = long long;
    auto big_cmp_gre = [&](ll a, ll b, ll c, ll d) {
        if (a == 0) return true;
        if (c == 0) return false;
        if (b / a < d / c) return true;
        if (b / a > d / c) return false;
        return b % a * c <= d % c * a; // a/b >= c/d
    };
    
bool BIG_CMP_GR(ll a, ll b, ll c, ll d) {
    if (d == 0) return 0;
    if (b == 0) return 1;
    if (a / b > c / d) return 1;
    if (a / b < c / d) return 0;
    return BIG_CMP_LS(b, a % b, d, c % d);
}

bool BIG_CMP_LS(ll a, ll b, ll c, ll d) {
    if (d == 0) return 1;
    if (b == 0) return 0;
    if (a / b < c / d) return 1;
    if (a / b > c / d) return 0;
    return BIG_CMP_GR(b, a % b, d, c % d);
}