/**
 * @author Miguel Mini
 * @tag dp, amortized
 * @use: 
 *    - minimum number of deleted edges to
 *    isolate a connect k-componente.
 * @complexity O(nk)
**/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 410;
using ii = pair<int, int>;
vector<ii> g[maxn];
int n, k;
int sz[maxn];
int dp[maxn][maxn];
vector<vector<int>> tr[maxn];
 
void dfs(int x, int p) {
	sz[x] = 1;
	for (int i = 1; i <= k; ++i) dp[x][i] = 1e9;
	dp[x][1] = 0;
	for (int d = 0; d < g[x].size(); ++d) {
		int v = g[x][d].first;
		tr[x].push_back(vector<int>(k+1));
		if (v == p) continue;
		dfs(v, x);
		int tdp[k + 1];
		for (int i = 1; i <= k; ++i) tdp[i] = dp[x][i] + 1;
		for (int i = min(k, sz[v]+sz[x]); i >= 1; --i) {
			for (int j = min(i-1, sz[v]); j >= max(1, i-sz[x]); --j) {
				int temp = dp[x][i-j] + dp[v][j];
				if (tdp[i] > temp) {
					tdp[i] = temp;
					tr[x][d][i] = j;
				}
			}
		}
		for (int i = 1; i <= k; ++i) dp[x][i] = tdp[i];
		sz[x] += sz[v];
	}
}
 
void get(int u, int p, int k, vector<int>& edges) {
	//cout << u << " " << p << " " << k << endl;
	for (int i = (int)g[u].size()-1; i >= 0; --i) {
		int v = g[u][i].first;
		int id = g[u][i].second;
		if (v == p) continue;
		if (tr[u][i][k] > 0) {
			get(v, u, tr[u][i][k], edges);
			k -= tr[u][i][k];
		} else {
			edges.push_back(id);
		}
	}
}
 
int main() {
	cin >> n >> k;
	for (int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back({b, i+1});
		g[b].push_back({a, i+1});
	}
	dfs(1, 0);
	int v = 1;
	for (int i = 2; i <= n; ++i) dp[i][k] += 1;
	for (int i = 2; i <= n; ++i) {
		if (dp[i][k] < dp[v][k]) v = i;
	}	
	//cout << dp[v][k] << endl;
	dfs(v, 0);
	vector<int> edges;
	get(v, 0, k, edges);
	sort(edges.begin(), edges.end());
	cout << edges.size() << '\n';
	for (int v : edges) cout << v << ' ';
	cout << '\n';
	return 0;
}
