int parent[maxn];
vector<int> aux[maxn];
vector<int> auxiliary_tree(vector<int> nodes) {
  vector<int> closed = nodes;
  sort(nodes.begin(), nodes.end(), [&](int u, int v) {
     return lo[u] < lo[v]; 
  });
  for (int i = 1; i < nodes.size(); ++i) {
      closed.push_back(lca(nodes[i-1], nodes[i]));
  }
  sort(closed.begin(), closed.end(), [&](int u, int v) {
      return lo[u] < lo[v];    
  });
  closed.resize(unique(closed.begin(), closed.end()) - closed.begin());
  for (int v : closed) aux[v].clear();
  stack<int> s;
  s.push(closed[0]);
  parent[closed[0]] = 0;
  for(int i = 1; i < closed.size(); ++i) {
    while (!s.empty() && hi[s.top()] < lo[closed[i]]) s.pop();
    aux[s.top()].push_back(closed[i]);
    parent[closed[i]] = s.top();
    s.push(closed[i]);
  }
  return closed;
}
