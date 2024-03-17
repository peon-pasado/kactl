/**
 * Author Miguel Mini
 * @name BFS-TRANPOSE
 * @input: a graph g with nodes between 0 and sz(g)-1.
 * @output: number of components, nodes in each component and distance from node src.
 * @complexity: O(|V| + |E|)
 * Description: Todo
**/

int bfs_tranpose(int src, vector<vector<int>>& g, vector<vector<int>>& components, vector<int>& dist) {
	int n = g.size();
	vector<int> inB(n, -1);
	vector<int> B(n);
	for (int i = 0; i < n; ++i) {
		B[i] = i;
		dist[i] = 1e9;
	}
	dist[src] = 0;
	swap(B.back(), B[src]);
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
