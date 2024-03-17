/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

using ll = long long;
using ull = unsigned long long;
using ld = long double;
const ll mod = 1e18 + 3;
ll B = 1e5 + rand() % 100000;

vector<ll> pot = {1};

ll add(ll a, ll b) {
    return a+b<mod?a+b:a+b-mod;
}

ll mul(ull a, ull b, ull M=mod) {
	ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
	return ull(ret + M * (ret < 0) - M * (ret >= (ll)M));
}

ll get_pot(int i) {
    while (pot.size() <= i) {
        pot.push_back(mul(pot.back(), B));
    }
    return pot[i];
}

struct MyHash {
    ll v;

    MyHash(ll x) {v = x;}

    MyHash(char c) {v = c;}

    MyHash operator+(MyHash x) {
        return MyHash(add(v, x.v));
    }

    MyHash operator-(MyHash x) {
        return MyHash(add(v, mod - x.v));
    }

    bool operator==(MyHash x) {
        return v == x.v;
    }

    MyHash shift(int d) {
        return mul(v, get_pot(d));
    }

};

template<class MyHash>
struct StringHash {
    vector<MyHash> hash;

    size_t size() {
        return hash.size();
    }

    MyHash get_hash(int l, int r) {
        if (l == 0) return hash[r];
        return hash[r] - hash[l-1].shift(r-l+1);
    }

    void append(char c) {
        if (hash.empty()) hash.push_back(MyHash(c));
        else hash.push_back(hash.back().shift(1) + MyHash(c));
    }
};
