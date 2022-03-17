#include <bits/stdc++.h>
#define rep(i, n) for (int i=0; i<n; ++i)
#define trav(e, v) for (auto e : v)
#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())
using namespace std;

using vi=vector<int>;
const int maxn = 1000 + 10;
const int sigma = 26;
using ll = long long;

void format(string& s) {
    for (auto& ch : s) ch-='a'; //change
}

struct AC {
    vector<vi> nxt, go;
    vector<string> S;
    vector<ll> H;
    vector<ll> leaf;//change
    vector<ll> value;
    vi lnk;
    AC() {}
    int size() {
        return S.size();
    }
    void add_str(string& v, ll h) {
        format(v);
        S.emplace_back(move(v));
        H.emplace_back(h);
    }
    void build() {
        make_trie();
        //make_automaton();
    }
    size_t add_tr() {
        nxt.emplace_back(vi(sigma));
        leaf.emplace_back(0);//change
        return sz(nxt) - 1;
    }
    void add_trie(const string& s, ll h) {
        size_t r=0;
        for (const auto& c : s) {
            if (!nxt[r][c]) nxt[r][c]=add_tr();
            r = nxt[r][c];
        }
        leaf[r] += h;
    }
    void make_trie() {
        add_tr();
        rep(i, sz(S)) {
            add_trie(S[i], H[i]);
        }
    }
    void make_automaton() {
        go.assign(sz(nxt), vi(sigma, 0));
        lnk.assign(sz(nxt), 0);
        value.assign(sz(nxt), 0);
        queue<int> Q;
        Q.push(0);
        while (!Q.empty()) {
            int q = Q.front(); Q.pop();
            value[q] = leaf[q] + value[lnk[q]]; //change
            rep(i, sigma) {
                if (nxt[q][i]) {
                    lnk[go[q][i]=nxt[q][i]] = (q>0)*go[lnk[q]][i];
                    Q.emplace(nxt[q][i]); 
                } else {
                    go[q][i] = (q>0)*go[lnk[q]][i];
                }
            }
        }
    }
    void merge_dsu(AC& other) {
        rep(i, sz(other.S)) {
            add_trie(other.S[i], other.H[i]);
            this->S.emplace_back(other.S[i]);
            this->H.emplace_back(other.H[i]);
        }
        //make_automaton();
    }
    friend AC merge(const AC& L, const AC& R) {
        AC M;
        M.S.insert(M.S.end(), all(L.S));
        M.S.insert(M.S.end(), all(R.S));
        M.H.insert(M.H.end(), all(L.H));
        M.H.insert(M.H.end(), all(R.H));
        M.build();
        return move(M);
    }
};
