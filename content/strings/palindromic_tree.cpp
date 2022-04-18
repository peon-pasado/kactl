/*
 * Problem: 2014-2015 ACM-ICPC, Asia Xian Regional Contest - The Problem to Slow Down You
 * Given two strings s and t, counts the number of common substrings between s and t
 * such that all of them are palindromes.
 *
 * Complexity: O(|s| + |t|) per case.
*/

#include<bits/stdc++.h>
using namespace::std;

const int E = 26;
const int MAX = 400000 + 5;

struct node{
	int len;
	int link;
	int go[E];
	long long cnt[2];
	node(){}
	void clear(){
		memset(cnt, 0, sizeof cnt);
		memset(go, 0, sizeof go);
	}
};

int last;
int nodes;
char s[MAX];
node tree[MAX];

void init(){
	tree[0].clear(); tree[1].clear();
	tree[0].link = tree[1].link = 0;
	tree[0].len = -1;
	tree[1].len = 0;
	last = 1;
	nodes = 2;
}

void extend(int pos, int id){
	int c = s[pos] - 'a';
	int cur = last;
	while(true){
		if(pos - tree[cur].len - 1 >= 0 and s[pos - tree[cur].len - 1] == s[pos]) break;
		cur = tree[cur].link;
	}
	if(tree[cur].go[c]){
		last = tree[cur].go[c];
		tree[last].cnt[id]++;
		return;
	}
	tree[nodes].clear();
	last = nodes++;
	tree[last].len = tree[cur].len + 2;
	tree[cur].go[c] = last;
	tree[last].cnt[id]++;

	if(tree[last].len == 1){
		tree[last].link = 1;
		return;
	}
	while(true){
		cur = tree[cur].link;
		if(pos - tree[cur].len - 1 >= 0 and s[pos - tree[cur].len - 1] == s[pos]){
			tree[last].link = tree[cur].go[c];
			break;
		}
	}
}

void insert(int id){
	last = 1;
	for(int i = 0; s[i]; i++){
		extend(i, id);
	}
}

long long solve(){
	for(int i = nodes - 1; i > 0; i--){
		int p = tree[i].link;
		for(int j = 0; j < 2; j++){
			tree[p].cnt[j] += tree[i].cnt[j];
		}
	}
	long long ans = 0;
	for(int i = 0; i < nodes; i++){
		if(tree[i].len <= 0) continue;
		ans += tree[i].cnt[0] * tree[i].cnt[1];
	}
	return ans;
}

int main(){
	int t;
	int caso = 1;
	scanf("%d", &t);
	while(t--){
		init();
		for(int i = 0; i < 2; i++){
			scanf("%s", s);
			insert(i);
		}
		printf("Case #%d: %lld\n", caso++, solve());
	}
	return 0;
}

