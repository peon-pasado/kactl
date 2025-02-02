/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

#include<bits/stdc++.h>
using namespace::std;


struct SuffixAutomaton {
	int nodes;
	vector<int> link; // suffix link
	vector<int> len; // max length of the state
	vector<int> firstpos; // last position of first occurrence of state
	vector<vector<int>> nxt; // transitions
	vector<bool> is_clone; // clone attribute (for counting)

	SuffixAutomaton() {
		len.emplace_back(0);
		link.emplace_back(-1);
		nxt.emplace_back(vector<int>(26, 0));
		firstpos.emplace_back(-1);
		is_clone.emplace_back(false);
		nodes = 1;
	}

	void add_node(int new_len, int new_link, int new_fp, bool new_clone) {
		len.emplace_back(new_len);
		link.emplace_back(new_link);
		nxt.emplace_back(vector<int>(26, 0));
		firstpos.emplace_back(new_fp);
		is_clone.emplace_back(new_clone);
	}

	int add(int p, int c) {
		auto getNxt = [&] () {
			if (p == -1) return 0;
			int q = nxt[p][c]; 
			if (len[p] + 1 == len[q]) return q;
			int clone = nodes++;
			add_node(len[p] + 1, link[q], firstpos[q], true);
			nxt[nodes - 1] = nxt[q];
			link[q] = clone;
			while(~p and nxt[p][c] == q) {
				nxt[p][c] = clone;
				p = link[p];
			}
			return clone;
		};
		// if (nxt[c][p]) return getNxt();
		// ^ need if adding > 1 string
		int cur = nodes++; // make new state
		add_node(len[p] + 1, -1, firstpos[p] + 1, false);
		while(~p and !nxt[p][c]) {
			nxt[p][c] = cur;
			p = link[p];
		}
		int x = getNxt(); 
		link[cur] = x; 
		return cur;
	}

	void init(string s) { // add string to automaton
		int p = 0; 
		for(auto c : s) {
			p = add(p, c - 'a');
		}
	} 
};

const int E = 26;
const int N = 90000 + 5;
const int SUML = 2 * N;

int n;
int q;
int L;
int last;
int nodes;
char s[N];
int p[SUML];
int head[N];
long long memo[SUML];
SuffixAutomaton Solver;

void preprocess(){
	for(int i = 0; i < Solver.nodes; i++) head[Solver.len[i]]++;
	int sum = 0;
	for(int i = 0; i <= n; i++){
		sum += head[i];
		head[i] = sum - head[i];
	}
	for(int i = 0; i < Solver.nodes; i++) p[head[Solver.len[i]]++] = i;
	for(int i = Solver.nodes - 1; i >= 0; i--){
		int at = p[i];
		memo[at] = 0;
		for(int c = 0; c < E; c++){
			if(Solver.nxt[at][c]) memo[at] += memo[Solver.nxt[at][c]] + 1;
		}
	}
}

int main(){
	cin.tie(0) -> sync_with_stdio(false);
	string s;
	cin >> s;
	n = s.size();
	Solver.init(s);
	preprocess();
	cin >> q;
	int k;
	while(q--){
		cin >> k;
		int pos = 0;
		while(k > 0){
			if(k == 0) break;
			for(int c = 0; c < E; c++){
				int v = Solver.nxt[pos][c];
				if(!v) continue;
				if(memo[v] + 1 >= k){
				    cout << char('a' + c);
					k--;
					pos = v;
					break;
				}
				k -= memo[v] + 1;
			}
		}
		cout << '\n';
	}
	return 0;
}
