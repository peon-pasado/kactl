/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

#define set_to(container, value) fill(begin(container), end(container), value)

const int inf = 1e9;

typedef pair<int, int> ii;

struct MinCostMaxFlow {
    struct Edge {
        int to, cap, flow, cost, link;
        Edge() {}
        Edge(int to, int cap, int cost, int link, int flow=0):
                to(to), cap(cap), link(link), flow(flow), cost(cost) {}
    };
    vector<vector<Edge>> g;
    vector<int> d, p;
 
    MinCostMaxFlow(int n): g(n), d(n), p(n) {}
 
    void addEdge(int a, int b, int cost, int cap) {
        if (a == b) return;
        int pa = sz(g[a]), pb = sz(g[b]);
        g[a].emplace_back(b, cap, cost, pb); g[b].emplace_back(a, 0, -cost, pa);
    }
 
    bool spfa(int src, int snk) {
        set_to(d, inf); set_to(p, -1);
        priority_queue<ii, vector<ii>, greater<ii>> Q;
        Q.push({d[src] = 0, src});
        while (!Q.empty()) {
            auto q = Q.top(); Q.pop();
            int x = q.second;
            int w = q.first;
            if (x == snk) return 1;
            if (d[x] < w) continue;
            rep(i, 0, sz(g[x])) {
                auto e = g[x][i];
                if (e.flow < e.cap and w + e.cost < d[e.to]) {
                    d[e.to] = w + e.cost;
                    p[e.to] = e.link;
                    Q.push({d[e.to], e.to});
                }
            }
        }
        return 0;
    }
 
    int solve(int s, int t, int k) {
        int flow = 0, cost = 0;
        while (flow < k) {
            if (!spfa(s, t)) break;
            int f = k - flow;
            int cur = t;
            while (cur != s) {
                auto e = g[cur][p[cur]];
                int push = g[e.to][e.link].cap - g[e.to][e.link].flow;
                f = min(f, push);
                cur = e.to;
            }
            flow += f;
            cost += f * d[t];
            cur = t;
            while (cur != s) {
                auto& e = g[cur][p[cur]];
                e.flow -= f;
                g[e.to][e.link].flow += f;
                cur = e.to;
            }
        }
        return flow < k ? -1 : cost;
    }
};
