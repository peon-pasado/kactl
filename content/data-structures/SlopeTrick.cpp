/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

struct SlopeTrick {
	//public:
		//Constructor
	SlopeTrick() :minf(0), addR(0), addL(0) {}
 
	//Add x-a to the right
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
	//Add a-x to the left
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
	//Add to both sides
	void push(long long a) { pushR(a); pushL(a); }
	//Add a constant
	void addmin(long long a) { minf += a; }
	//The endpoints of the interval with a slope of 0
	pair<long long, long> getZero() {
		pair<long long, long long>p = { -LINF,LINF };
		if (0 != Lque.size()) { p.first = Lque.top() + addL; }
		if (0 != Rque.size()) { p.second = Rque.top() + addR; }
		return p;
	}
	//Cumulative min
	void CumulativeMin() { Rque = priority_queue<long long, vector<long long>, greater<long long>>(); }
	//Right cumulative min
	void CumulativeMinR() { Lque = priority_queue<long long>(); }
	//Function restoration (slow. Not recommended?)
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
		//If you need to revert it
		//rep(i, vL.size()) { Lque.push(vL[i] - addL); }
		//rep(i, vR.size()) { Rque.push(vR[i] - addR); }
	}
	//Restoring the function (slow. Not recommended?)
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
	//Right slide
	void SlideR(long long x) { addR += x; }
	//Left slide
	void SlideL(long long x) { addL += x; }
	//Full slide (unlimited)
	void Slid(long long x) { SlideL(x), SlideR(x); };
	//Full slide (it breaks if addL <= addR)
	//g(x) = min f(y) y in [x-b,x-a]
	void Slid(long long b, long long a) { SlideL(a), SlideR(b); };
	//Merge (the source of the merge will no longer be usable thereafter.)
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
 
	priority_queue<long long> Lque;	//Left side (in descending order)
	priority_queue<long long, vector<long long>, greater<long long>> Rque;	//Right side (in ascending order)
	long long minf;					//Minimum value
	long long addR;					//The number that is added to all elements of the right-side set
	long long addL;					//The number that is added to all elements of the left-side set
};
