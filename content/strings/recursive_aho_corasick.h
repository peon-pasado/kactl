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
	} T[maxn], A[maxn];
	int p[maxn];
	char inc[maxn];
	bool match[maxn];
	int S[maxn], L[maxn];
	int len[maxn];
	int n = 1;
	Aho_Corasick() {
		memset(S, -1, sizeof S);
		memset(L, -1, sizeof L);
		memset(match, 0, sizeof match);
		p[0] = len[0] = 0;
	}
	void add(const string& s, int r=0) {
		for (auto c : s) {
			if (T[r][c] < 0) {
				len[n] = len[r] + 1;
				T[p[n]=r][inc[n]=c] = n;
				n += 1;
			}
			r = T[r][c]; 
		}
		match[r] = 1;
	}
	int go(int x, char c) {
		if (~A[x][c]) return A[x][c];
		if (~T[x][c]) return A[x][c]=T[x][c];
		return A[x][c] = x ? go(suff(x), c) : 0; 
	}
	int suff(int x) {
		if (~S[x]) return S[x];
		return S[x] = p[x] ? go(suff(p[x]), inc[x]) : 0;
	}
	int super(int x){
    if (~L[x]) return L[x];
    if (!x) return L[x]=0; 
    if (match[suff(x)]) return L[x]=suff(x);
    return L[x]=super(suff(x));
  }
  bool has_match(int x) {
    return match[x] || super(x);	
  }
	int len_match(int x) {
    if (match[x]) return len[x];
    return len[super(x)];
  }
};
