/**
 * @Author Miguel Mini
 * @name BFS-TRANPOSE
 * @input: a graph g with nodes between 0 and sz(g)-1.
 * @output: number of components, nodes in each component and distance from node 0.
 * @complexity: O(|V| + |E|)
**/

int bfs_tranpose(vector<vector<int>>& g, vector<vector<int>>& components, vector<int>& dist) {
	vector<int> inB(g.size(), -1);
	vector<int> B(g.size());
	for (int i = 0; i < n; ++i) {
		B[i] = (int)g.sizze()-1-i;
		dist[i] = 1e9;
	}
	dist[0] = 0;
	int n_components = 0;
	do {
		queue<int> Q;
		Q.push(B.back());
		B.pop_back();
    		components.push_back(vector<int>());
		//open component
		while (!Q.empty()) {
			int q = Q.front(); Q.pop();
			//q is a component node
      			components.back().push_back(q);
			for (int u : g[q]) inB[u] = q;
			int j = 0;
			for (int i = 0; i < B.size(); ++i)
				if (inB[B[i]] == q) B[j++] = B[i];
				else {
					dist[B[i]] = dist[q] + 1;
					Q.push(B[i]);
				}
			B.resize(j);
		}
		n_components++;
		//close component
	} while (!B.empty());
	return n_components;
}
