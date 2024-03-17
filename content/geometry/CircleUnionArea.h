/**
 * Author: Rating MiSeRable
 * Date: 2020-10-01
 * License: CC0
 * Source: ?
 * Description: Todo
 */

template<class T>
struct CircleUnionArea{
	const double PI = acos(-1.0);
	const double LAP = 2 * PI;
	const double EPS = 1e-8;
	int n;
	vector<T> x, y, r;

	typedef pair<double, int> node;

	CircleUnionArea(vector<T> &X, vector<T> &Y, vector<T> &R){
		n = X.size();
		assert(Y.size() == n and R.size() == n);
		x = X;
		y = Y;
		r = R;
		fix();
	}

	inline int sgn(double x){
		return (x > EPS) - (x < -EPS);
	}

	void fix(){
		vector<int> p(n);
		iota(p.begin(), p.end(), 0);
		sort(p.begin(), p.end(), [&] (int i, int j){ return r[i] < r[j];});
		vector<bool> usable(n, true);
		for(int i=0; i<n; i++){
			if(sgn(r[p[i]]) <= 0){
				usable[p[i]] = false;
			}
			if(!usable[p[i]]) continue;
			for(int j=i+1; j<n; j++){
				if(!usable[p[j]]) continue;
				if(sgn(hypot(x[p[i]] - x[p[j]], y[p[i]] - y[p[j]]) + r[p[i]] - r[p[j]]) <= 0){
					usable[p[i]] = false;
					break;
				}
			}
		}
		vector<T> new_x, new_y, new_r;
		for(auto i : p){
			if(!usable[i]) continue;
			new_x.emplace_back(x[i]);
			new_y.emplace_back(y[i]);
			new_r.emplace_back(r[i]);
		}
		swap(new_x, x);
		swap(new_y, y);
		swap(new_r, r);
		n = x.size();
	}

	inline void inter(int i, int j, double &a, double &b){
		double dx = x[j] - x[i];
		double dy = y[j] - y[i];
		double d = dx * dx + dy * dy;
		double alpha = acos((d + r[i] * r[i] - r[j] * r[j]) * 0.5 / (sqrt(d) * r[i]));
		double central = atan2(dy, dx);
		a = central - alpha;
		b = central + alpha;
		if(a < 0) a += LAP;
		if(b < 0) b += LAP;
	}

	double getArea(int i, double L, double R){
		double d = R - L;
		double xL = x[i] + r[i] * cos(L), yL = y[i] + r[i] * sin(L);
		double xR = x[i] + r[i] * cos(R), yR = y[i] + r[i] * sin(R);
		return ((d - sin(d)) * r[i] * r[i] + (xL * yR - xR * yL));
	}

	double add(int pos){
		double ans = 0.0;
		vector< node > angles;
		for(int i=0; i<n; i++){
			if(i == pos) continue;
			if(hypot(x[pos] - x[i], y[pos] - y[i]) >= r[pos] + r[i] + 1e-9) continue;
			double L, R;
			inter(pos, i, L, R);
			angles.emplace_back(make_pair(L, 1));
			angles.emplace_back(make_pair(R, -1));
			if(sgn(L - R) > 0){
				angles.emplace_back(make_pair(0, 1));
				angles.emplace_back(make_pair(LAP, -1));
			}

		}
		if(angles.empty()) return LAP * r[pos] * r[pos];
		sort(angles.begin(), angles.end(), [&] (node a, node b){
			if(sgn(a.first - b.first) == 0) return b.second < a.second;
			return sgn(a.first - b.first) < 0;
		});
		ans += getArea(pos, 0, angles[0].first) + getArea(pos, angles.back().first, LAP);
		int balance = 0;
		for(int i = 0; i + 1 < angles.size(); i++){
			balance += angles[i].second;
			if(!balance){
				ans += getArea(pos, angles[i].first, angles[i+1].first);
			}
		}
		return ans;
	}

	double solve(){
		double ans = 0.0;
		for(int i=0; i<n; i++){
			double act = add(i);
			ans += act;
		}
		ans *= 0.5;
		return ans + EPS;
	}
};
