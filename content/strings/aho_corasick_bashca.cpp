#include <bits/stdc++.h>
#define rep(i, n) for (int i=0; i<n; ++i)
#define trav(e, v) for (auto e : v)
#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())
using namespace std;

using vi=vector<int>;
const int maxn = 1000000 + 10;
const int sigma = 26;
using ll = long long;

struct AC {
    vector<vi> nxt, go;
    vector<string> S;
    vector<bool> leaf;//change
    vi lnk;
    AC() {}
    void add_str(string& v) {
        for (auto& ch : v) ch-='a'; //change
        S.emplace_back(move(v));
    }
    void build() {
        make_trie();
        make_automaton();
    }
    size_t add_tr() {
        nxt.emplace_back(vi(sigma));
        leaf.emplace_back(0);//change
        return sz(nxt) - 1;
    }
    void add_trie(const string& s) {
        size_t r=0;
        for (const auto& c : s)
            r = nxt[r][c] ?: add_tr();
        leaf[r] = 1; //change
    }
    void make_trie() {
        add_tr();
        for (const auto& s : S) add_trie(s);
    }
    void make_automaton() {
        go.assign(sz(nxt), vi(sigma, 0));
        lnk.assign(sz(nxt), 0);//change
        queue<int> Q;
        while (!Q.empty()) {
            int q = Q.front(); Q.pop();
            leaf[q] = leaf[lnk[q]]; //change
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
        for (const auto& s : other.S) {
            add_trie(s);
            this->S.emplace_back(s);
        }
        make_automaton();
    }
    friend AC merge(const AC& L, const AC& R) {
        AC M;
        M.S.insert(M.S.end(), all(L.S));
        M.S.insert(M.S.end(), all(R.S));
        M.build();
        return move(M);
    }
};
