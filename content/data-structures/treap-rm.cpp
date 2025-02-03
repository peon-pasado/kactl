/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

#include <bits/stdc++.h>
using namespace std;
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<> dis(1, 2e9);
const int inf = 2e9;
struct implicit_treap { //0-base index
	struct Node {
		int pr, v, m;
		int l, r, c;
		//int p;
		bool rev;
		Node() {}
		Node(int v): v(v), m(v), pr(dis(rng)), c(1) {/**p=**/rev=l=r=0;}
	};
	static const int maxn = 1e5 + 10;
	Node T[maxn];
	int e;
	implicit_treap():e(0) {}
	int cnt(int t) {return t ? T[t].c : 0;}
	int mx(int t) {return t ? T[t].m : -inf;}
	void upd(int t) {
		if (t) {
			T[t].c = cnt(T[t].l) + 1 + cnt(T[t].r);
			T[t].m = max({mx(T[t].l), T[t].v, mx(T[t].r)});
			//if (T[t].l) T[T[t].l].p = t;
			//if (T[t].r) T[T[t].r].p = t;
		}
	}
	void push(int t) {
		if (t && T[t].rev) {
			swap(T[t].l, T[t].r);
			if (T[t].l) T[T[t].l].rev ^= 1;
			if (T[t].r) T[T[t].r].rev ^= 1;
			T[t].rev = 0;
		}
	}
	void split(int t, int& l, int& r, int k, int add=0) { //[...key)[key...]
		if (!t) return void(l=r=0);
		push(t);
		int i_k = cnt(T[t].l)+add; 
		if (i_k < k) split(T[t].r, T[t].r, r, k, i_k+1), l=t;
		else split(T[t].l, l, T[t].l, k, add), r=t;
		upd(t);
	}
	void merge(int& t, int l, int r) { //(< height)->(> priority)
		push(l); push(r);
		if (!l || !r) t=l^r;
		else if (T[l].pr>T[r].pr) merge(T[l].r, T[l].r, r), t=l;
		else merge(T[r].l, l, T[r].l), t=r;
		upd(t);
	}
	void add(int& t, int p, int v, int x=0) {
		split(t, t, x, p);
		T[++e] = Node(v);
		merge(x, e, x);
		merge(t, t, x);
	}
	void erase(int& t, int p, int x=0, int y=0) {
		split(t, t, y, p);
		split(y, x, y, p+1);
		merge(t, t, y);
	}
	void query(int& t, int l, int r, int x=0, int y=0) {
		split(t, t, x, l);
		split(x, x, y, r-l+1);
		if (x) T[x].rev ^= 1;
		merge(t, t, x);
		merge(t, t, y);
	}
	int kth(int t, int k) { //0-base
		if (!t) return 0;
		push(t);
		int i_k=cnt(T[t].l);
		if (i_k==k) return t;
		return kth(i_k<k?T[t].r:T[t].l, k-(i_k<k)*(i_k+1));
	}
	//int ord(int nd, bool ri=1) { //given a node return its order
	//	if (!nd) return -1;
	//	push(nd);
	//	return 1 + ri*cnt(T[nd].l) + ord(T[nd].p, T[T[nd].p].r==nd);	
	//}
	int max_ord(int t) {
		if (!t) return -1;
		push(t);
		if (T[t].v==T[t].m) return cnt(T[t].l);
		if (mx(T[t].l)==T[t].m) return max_ord(T[t].l);
		return cnt(T[t].l)+1+max_ord(T[t].r);
	}
};
