/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

#include <bits/stdc++.h>
using namespace std;

struct BipartiteMatcher {
	vector<vector<int>> g;
	vector<int> L, R;
	vector<bool> vis;
	
	BipartiteMatcher(int n, int m):
		g(n), L(n, -1), R(m, -1), vis(n) {} 

	void addEdge(int a, int b) {
		g[a].emplace_back(b);
	}

	bool match(int x) {
		if (vis[x]) return 0;
		vis[x] = 1;
		for (int v : g[x])
			if (R[v] == -1)
				return R[L[x]=v]=x, 1;
		for (int v : g[x])
			if (match(R[v]))
				return R[L[x]=v]=x, 1;
		return 0;
	}
	
	int solve() {
		int cnt = 1;
		//vector<int> ind(L.size());
		//for (int i = 0; i < ind.size(); ++i) {
		//	ind[i] = 1;
		//}
		//shuffle(ind.begin(), ind.end(), rng);
		while (cnt--) {
			fill(vis.begin(), vis.end(), 0);
			for (int i = 0; i < L.size(); ++i) {
				cnt |= L[i] == -1 and match(i);
			}
		}
		int res = 0;
		for (int i = 0; i < L.size(); ++i) {
			res += L[i] != -1;
		}
		return res;
	}
};


int main() {
	BipartiteMatcher(10, 10);
	return 0;
}
