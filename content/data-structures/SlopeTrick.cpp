/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

struct SlopeTrick {
	//public:
		//コンストラクタ
	SlopeTrick() :minf(0), addR(0), addL(0) {}
 
	//x-aを右に加算する
	void pushR(long long a) {
		if (0 == Lque.size()) {
			Rque.push(a - addR);
		}
		else {
			long long l0 = Lque.top() + addL;
			Lque.push(a - addL);
			long long x = Lque.top() + addL;
			Lque.pop();
			Rque.push(x - addR);
			minf += max((long long)0, l0 - a);
		}
	}
	//a-xを左に加算する
	void pushL(long long a) {
		if (0 == Rque.size()) {
			Lque.push(a - addL);
		}
		else {
			long long r0 = Rque.top() + addR;
			Rque.push(a - addR);
			long long x = Rque.top() + addR;
			Rque.pop();
			Lque.push(x - addL);
			minf += max((long long)0, a - r0);
		}
	}
	//両側追加
	void push(long long a) { pushR(a); pushL(a); }
	//定数追加
	void addmin(long long a) { minf += a; }
	//傾きが0の区間の両端
	pair<long long, long> getZero() {
		pair<long long, long long>p = { -LINF,LINF };
		if (0 != Lque.size()) { p.first = Lque.top() + addL; }
		if (0 != Rque.size()) { p.second = Rque.top() + addR; }
		return p;
	}
	//累積min
	void CumulativeMin() { Rque = priority_queue<long long, vector<long long>, greater<long long>>(); }
	//右側累積min
	void CumulativeMinR() { Lque = priority_queue<long long>(); }
	//関数の復元(遅い。非推奨？)
	vector<long long> Fx(vector<long long> &X) {
		vector<long long>vL;
		vector<long long>vR;
		vector<long long>ret(X.size());
		while (!Lque.empty()) {
			vL.push_back(Lque.top() + addL);
			Lque.pop();
		}
		while (!Rque.empty()) {
			vR.push_back(Rque.top() + addR);
			Rque.pop();
		}
		rep(i, X.size()) {
			long long num = minf;
			rep(j, vL.size()) { num += max((long long)0, vL[j] - X[i]); }
			rep(j, vR.size()) { num += max((long long)0, X[i] - vR[j]); }
			X[i] = num;
		}
		//元に戻す必要があれば
		//rep(i, vL.size()) { Lque.push(vL[i] - addL); }
		//rep(i, vR.size()) { Rque.push(vR[i] - addR); }
	}
	//関数の復元(遅い。非推奨？)
	long long FxSimple(long long X) {
		vector<long long>vL;
		vector<long long>vR;
		long long ret = minf;
		while (!Lque.empty()) {
			ret += max((long long)0, (Lque.top() + addL) - X);
			Lque.pop();
		}
		while (!Rque.empty()) {
			ret += max((long long)0, X - (Rque.top() + addR));
			Rque.pop();
		}
		return ret;
	}
	//右側スライド
	void SlideR(long long x) { addR += x; }
	//左側スライド
	void SlideL(long long x) { addL += x; }
	//全体スライド(無制限)
	void Slid(long long x) { SlideL(x), SlideR(x); };
	//全体スライド(addL <= addRにならないと壊れる)
	//g(x) = min f(y) y∈[x-b,x-a]
	void Slid(long long b, long long a) { SlideL(a), SlideR(b); };
	//マージ(マージ元は以降使えなくなる。)
	void merge(SlopeTrick &st) {
		if ((Lque.size() + Rque.size()) < (st.Lque.size() + st.Rque.size())) {
			swap(Lque, st.Lque);
			swap(Rque, st.Rque);
			swap(minf, st.minf);
			swap(addR, st.addR);
			swap(addL, st.addL);
		}
		while (!st.Lque.empty()) {
			pushL(st.Lque.top());
			st.Lque.pop();
		}
		while (!st.Rque.empty()) {
			pushR(st.Rque.top());
			st.Rque.pop();
		}
		minf += st.minf;
		addR += st.addR;
		addL += st.addL;
	}
 
	priority_queue<long long> Lque;	//左側(大きい順)
	priority_queue<long long, vector<long long>, greater<long long>> Rque;	//右側(小さい順)
	long long minf;					//最小値
	long long addR;					//右側集合全てにたされる数
	long long addL;					//左側集合全てにたされる数
};
