/**
 * Author: anta
 * Date: ?
 * Source: ?
 * Description: Todo
 */

#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define rer(i,l,u) for(int (i)=(int)(l);(i)<=(int)(u);++(i))
#define reu(i,l,u) for(int (i)=(int)(l);(i)<(int)(u);++(i))
#define aut(v, x) __typeof(x) v = (x)
#define each(it,o) for(__typeof((o).begin()) it = (o).begin(); it != (o).end(); ++ it)
#define all(o) (o).begin(), (o).end()
#define pb(x) push_back(x)
#define mp(x,y) make_pair((x),(y))
#define mset(m,v) memset(m,v,sizeof(m))
#define INF 0x3f3f3f3f
#define INFL 0x3f3f3f3f3f3f3f3fLL

using namespace std;
typedef vector<int> vi; 
typedef pair<int,int> pii; 
typedef vector<pair<int,int> > vpii;
typedef long long ll; 
typedef vector<long long> vl; 
typedef pair<long long,long long> pll; 
typedef vector<pair<long long,long long> > vpll;
typedef vector<string> vs; 
typedef long double ld;


typedef double Num;
typedef short Var;
typedef vector<Num> Vec;
typedef vector<Vec> Mat;
const Num Inf = numeric_limits<Num>::infinity();
const Num NaN = numeric_limits<Num>::quiet_NaN();
#define IsNaN(x) (x != x)
const Num EPS = 1e-10;
inline bool isInteger(Num x) { return abs(floor(x) - x) <= EPS; }

Num simplex(const Mat& A, const Vec& b, const Vec& c, vector<Num> &out_assigns) {
	const int m = A.size(), n = A[0].size();
	Mat D(m+1, Vec(n+1)); vi id(n+m+1);
	rer(i, 0, n+m) id[i] = i;
	rep(i, m) {
		rep(j, n) D[i][j] = -A[i][j];
		D[i][n] = b[i];
	}
	rep(j, n) D[m][j] = c[j];
	while(1) {
		int r = m, s = n+m;
		rep(i, m) if(D[i][n] < -EPS && id[n+r] > id[n+i]) r = i;
		rep(j, n) if(D[m][j] > EPS && id[s] > id[j]) s = j;
		if(r == m && s == n + m) break;
		if(id[n + r] < id[s]) {
			s = n + m;
			rep(j, n) if(D[r][j] > EPS && id[s] > id[j]) s = j;
		}else {
			r = m;
			rep(i, m) if(D[i][s] < -EPS && id[n+r] > id[n+i]) r = i;
		}
		if(r == m) { /* Unbounded */ return Inf; }
		if(s == n + m) { /* NoSolution */ return NaN; }
		swap(id[s], id[n+r]);
		D[r][s] = 1. / D[r][s];
		rer(j, 0, n) if(j != s) D[r][j] *= -D[r][s];
		rer(i, 0, m) if(i != r && abs(D[i][s]) > EPS) {
			rer(j, 0, n) if(j != s) D[i][j] += D[r][j] * D[i][s];
			D[i][s] *= D[r][s];
		}
	}

	out_assigns.assign(n, 0);
	rep(i, m) if(id[n+i] < n)
		out_assigns[id[n+i]] = D[i][n];

	return D[m][n];
}
