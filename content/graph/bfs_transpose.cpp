/**
 * @Author Miguel Mini
 * @name BFS-TRANPOSE
 * @input: a graph g with nodes between 0 and sz(g)-1.
 * @output: number of components and nodes in each component.
**/

int bfs_tranpose(vector<vector<int>>& g, vector<vector<int>>& components) {
	vector<int> inB(g.size(), -1);
	vector<int> B(g.size());
	iota(B.begin(), B.end(), 0);
	int res = 0;
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
				else Q.push(B[i]);
			B.resize(j);
		}
		res++;
		//close component
	} while (!B.empty());
	return res;
}
