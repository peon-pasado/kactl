/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

struct CentroidDecomposition {
    const long double PI = acos(-1);
    typedef complex<double> cd;
	vector<vector<int>> T;
	vector<int> size, P, rank;
	vector<bool> block;
	vector<int> h;
	vector<int> L;
	vector<int> R;
	vector<int> order;
	vector<long long> res;
	int root;
	int timer;
	CentroidDecomposition(int n):
		T(n)
		, h(n)
		, size(n)
		, P(n, -1)
		, block(n, false)
		, rank(n)
		, root(0)
		, order(n)
		, L(n)
		, R(n)
		, res(n, 0)
	{}
	void addEdge(int a, int b) {
		T[a].emplace_back(b);
		T[b].emplace_back(a);
	}
	bool valid(int x, int p) {
		return x != p and not block[x];
	}
	int dfs(int x, int p=-1) {
		size[x] = 1;
		for (int v : T[x]) {
			if (valid(v, p)) {
				size[x] += dfs(v, x);
			}
		}
		return size[x];
	}
	int dfs2(int u, int p=-1){
		L[u] = timer;
		order[timer++] = u;
		int max_h = h[u];
		for(int v : T[u]){
			if(valid(v, p)){
				h[v] = h[u] + 1;
				max_h = max(max_h, dfs2(v, u));
			}
		}
		R[u] = timer - 1;
		return max_h;
	}
	int get_centroid(int x, int p, int n) {
		for (int v : T[x]) {
			if (valid(v, p) and size[v] > n>>1) {
				return get_centroid(v, x, n);
			}
		}
		return x;
	}
	void fft(vector<cd>& a) {
		int n = a.size(), L = 31 - __builtin_clz(n);
		static vector<complex<long double>> R(2, 1);
		static vector<cd> rt(2, 1);  // (^ 10% faster if double)
		for (static int k = 2; k < n; k *= 2) {
			R.resize(n); rt.resize(n);
			auto x = polar(1.0L, PI / k); // M_PI, lower-case L
			for(int i = k; i < 2*k; i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
		}
		vector<int> rev(n);
		for(int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
		for(int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
		for (int k = 1; k < n; k *= 2)
			for (int i = 0; i < n; i += 2 * k) for(int j = 0; j < k; j++) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
				auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
				cd z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
				a[i + j + k] = a[i + j] - z;
				a[i + j] += z;
			}
	}
	vector<long long> multiply(const vector<int> &A, const vector<int> &B) {
		vector<long long> result(A.size() + B.size() - 1);
		int L = 32 - __builtin_clz(result.size()), n = 1 << L;
		vector<cd> in(n), out(n);
		for(int i = 0; i < n; i++) in[i] = cd(i < A.size() ? A[i] : 0, i < B.size() ? B[i] : 0);
		fft(in);
		for(auto &x : in) x *= x;
		for(int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
		fft(out);
		for(int i = 0; i < result.size(); i++) result[i] = round(imag(out[i]) / (4 * n));
		while(result.size() > 1 and result.back() == 0) result.pop_back();
		return result;
	}
	void solve(int c, int p) {
        	timer = 0;
        	h[c] = 0;
		int H = dfs2(c) + 1;
        	vector<int> cur(H, 0);
        	for(int v : T[c]){
        		if(!valid(v, p)) continue;
        		for(int i = L[v]; i <= R[v]; i++){
				cur[h[order[i]]]++;
			}
			vector<long long> here = multiply(cur, cur);
			for(int j = 0; j < here.size(); j++){
				res[j] -= here[j];
			}
			for(int i = L[v]; i <= R[v]; i++){
				cur[h[order[i]]]--;
			}
		}
		for(int i = 0; i < timer; i++){
			cur[h[order[i]]]++;
		}
		vector<long long> here = multiply(cur, cur);
		for(int j = 0; j < here.size(); j++){
			res[j] += here[j];
		}
	}
	void decompose(int x, int p=-1) {
		int n = dfs(x);
		int cen = get_centroid(x, -1, n);
		solve(cen, p);
		P[cen] = p; 
		block[cen] = 1;
		for (auto v : T[cen]) {
			if (block[v]) continue;
			decompose(v, cen);
		}
	}
	vector<long long> get_distances(bool ordered = false){
		decompose(0);
		if(not ordered){
			for(auto &x : res) x >>= 1;
		}
		return res;
	}
};
