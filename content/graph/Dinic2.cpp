#include <bits/stdc++.h>
using namespace std;
#define SZ(x) x.size()
using ll = long long;
const int inf = 1e9;
struct Dinic {
	struct Edge {
		int to, cap, flow, link;
		Edge() {}
		Edge(int to, int cap, int link, int flow=0):
			to(to), cap(cap), link(link), flow(flow) {}
	};
	vector<vector<Edge>> g;
	vector<int> d, pt;
	
	Dinic(int n): g(n), d(n), pt(n) {}

	void addEdge(int a, int b, int cap) {
		if (a == b) return;
	  int posa = SZ(g[a]), posb = SZ(g[b]);
		g[a].emplace_back(b, cap, posb);
		g[b].emplace_back(a, 0, posa);
	}

	bool bfs(int src, int snk) {
		queue<int> q({src});
		fill(d.begin(), d.end(), 0xfffffff);
		d[src] = 0;
		while (not q.empty()) {
			int v = q.front(); q.pop();
			if (v == snk) return 1;
			for (auto e : g[v]) {
				if (e.flow >= e.cap) continue;
				if (d[e.to] > d[v] + 1) {
					d[e.to] = d[v] + 1;
					q.emplace(e.to);
				}
			}
		}
		return 0;
	}

	int dfs(int x, int snk, int flow=inf) {
		if (x == snk or not flow) return flow;
		for (; pt[x] < SZ(g[x]); ++pt[x]) {
			auto& e = g[x][pt[x]];
			if (d[e.to] == d[x] + 1) {
				int res = min(e.cap - e.flow, flow);
				if (int push = dfs(e.to, snk, res)) {
					e.flow += push;
					g[e.to][e.link].flow -= push;
					return push;
				}
			}
		}
		return 0;
	}

	ll solve(int s, int t) {
		ll res = 0;
		while (bfs(s, t)) {
			fill(pt.begin(), pt.end(), 0);
			while (int flow = dfs(s, t)) {
				res += flow;
			}
		}
		return res;
	}
};

