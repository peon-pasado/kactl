/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

const int maxn = 1e5 + 10;
struct Aho_Corasick {
	const static int sigma = 26;
	struct Trie {
		int nxt[sigma];
		static int ord(char c) {
			if (c < sigma) return c;
			return tolower(c) - 'a';
		}
		int& operator[](char c) {
			return nxt[ord(c)];
		}
		Trie() {
			memset(nxt, -1, sizeof nxt);
		}
	} T[maxn];
	bool match[maxn];
	int S[maxn], L[maxn];
	int len[maxn];
	int n = 1;
	Aho_Corasick() {
		memset(S, -1, sizeof S);
		memset(L, -1, sizeof L);
		memset(match, 0, sizeof match);
		S[0] = L[0] = 0;
		len[0] = 0;
	}
	void add(const string& s, int r=0) {
		for (auto c : s) {
			if (T[r][c] < 0) {
				len[n] = len[r] + 1;
				T[r][c] = n;
				n += 1;
			}
			r = T[r][c]; 
		}
		match[r] = 1;
	}

	void build(){
		queue<int> Q;
		Q.emplace(0);
		while(!Q.empty()){
			int u = Q.front();
			Q.pop();
			if(u) L[u] = match[S[u]]? S[u] : L[S[u]];
			for(int i = 0; i < sigma; i++){
				if(~T[u][i]){
					int v = T[u][i];
					S[v] = u ? T[S[u]][i] : 0;
					Q.emplace(v);
				}
				else{
					T[u][i] = u ? T[S[u]][i] : 0;
				}
			}
		}
	}

	int go(int x, int c){
		return T[x][c];
	}

  	bool has_match(int x) {
    		return match[x] || L[x];
  	}
	int len_match(int x) {
    		if (match[x]) return len[x];
    		return len[L[x]];
  	}
};
