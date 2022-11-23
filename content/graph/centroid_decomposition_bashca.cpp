#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 10;
const int maxl = 18;
using ll = long long;
vector<int> g[maxn];
int sz[maxn], pi[maxn];
bool blocked[maxn];
int n;

int find_centroid(int v, int parent, int n_v) {
  sz[v] = 1;
  int max_sz = 0;
  int centroid = 0;
  for (int u : g[v]) {
    if (!blocked[u] && (u ^ parent)) {
      centroid ^= find_centroid(u, v, n_v);
      sz[v] += sz[u];
      max_sz = max(max_sz, sz[u]);
    }
  }
  max_sz = max(max_sz, n_v - sz[v]);
  if (2 * max_sz <= n_v) 
    pi[centroid = v] = parent;
  return centroid;
}

int find_centroid(int v, int p, int n_v) {
  sz[v] = 1;
  int centroid = -1;
  for (int u : g[v]) {
    if (u == p || blocked[u]) continue;
    int c = find_centroid(u, v, n_v);
    sz[v] += sz[u];
    if (2 * sz[u] > n) centroid = c;
  }
  if (centroid==-1) centroid=v;
  return centroid;
}


void decompose(int x, int parent = -1, int n_v = n) {
  x = find_centroid(x, -1, n_v);
  if (~pi[x]) sz[pi[x]] = n_v - sz[x];
  pi[x] = parent;
  blocked[x] = 1;
  for (int v : g[x]) if (!blocked[v]) 
    decompose(v, x, sz[v]);
}

int TS;
int lo[maxn], hi[maxn], h[maxn];
int st[maxn][maxl];
void dfs(int x, int p = -1) {
  lo[x] = TS++;
  h[x] = p == -1 ? 0 : h[p] + 1;
  st[x][0] = p == -1 ? x : p;
  for (int k=1; k<maxl; ++k)
    st[x][k] = st[st[x][k-1]][k-1];
  for (int v : g[x]) {
    if (v ^ p) dfs(v, x);
  }
  hi[x] = TS++;
}

int lca(int u, int v) {
  if (h[u]>h[v]) swap(u, v);
  for (int k=maxl-1; k>=0; --k)
    if (h[st[v][k]]>=h[u]) v=st[v][k];
  if (u==v) return u;
  for (int k=maxl-1; k>=0; --k)
    if (st[u][k]!=st[v][k])
      u=st[u][k], v=st[v][k];
  return st[u][0];
}
 
void ancestor(int x){
	for(int v = x; ~v; v = pi[v])
		if (lo[v] <= lo[x] && hi[x] <= hi[v]) {
      		//<-update/query ancestor 
    	}
}

void descendant(int u, int x, int d) {
	for(int v=u; ~v; v=pi[v])
		if(lo[u] <= lo[v] && hi[v] <= hi[u]) {
			//<-update/query descendant
		}
}
