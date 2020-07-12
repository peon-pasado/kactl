template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const {return tie(x, y) < tie(p.x, p.y);}
	bool operator==(P p) const {return tie(x, y)==tie(p.x, p.y);}
	P operator+(P other) const {return P(x+other.x, y+other.y);}
	P operator-(P other) const {return P(x-other.x, y-other.y);}
	P operator*(T c) const {return P(x*c, y*c);}
	P operator/(T c) const {return P(x/c, y/c);}
	friend T operator*(T c, const P p) {return p*c;}
	T operator*(P other) const {return x*other.x + y*other.y;}
	T operator^(P other) const {return x*other.y - y*other.x;}
	T dot(P other) const {return (*this)*other;}
	T cross(P other) const {return (*this)^other;}
	T cross(P a, P b) const {return (a-*this).cross(b-*this);}
	T norm2() const {return x*x + y*y;}
	double norm() const {return sqrt((double)norm2());}
	double dist(P p) {return (p-(*this)).norm();}
	// angle to x-axis in interval [-pi, pi]
	double angle() const {return atan2(y, x);}
	P unit() const {return *this/norm();} // makes dist()=1
	P perp() const {return P(-y, x);} // rotates +90 degrees
	P normal() const {return perp().unit();}
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
	    return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));}
	P rotate(Point other, double a) const {
	    return (*this-other).rotate(a) + other;}
	friend istream& operator>>(istream& is, P& other) {
	    return is >> other.x >> other.y;}
	friend ostream& operator<<(ostream& os, P other) {
	    return os << "(" << other.x << "," << other.y << ")";}
};

template<class T>
struct Segment {
    Point<T> a, ab;
    bool isLine;
    Segment() {}
    Segment(Point<T> a, Point<T> b, bool isLine=false): 
    	a(a), ab(b - a), isLine(isLine) {}
    Point<T> b() {return a + ab;}
    bool intercept(Segment q) {
      T s = ab^q.ab;
      if (s == 0) { //parallel
      	if (((q.a - a)^ab) == 0) { //same line
      	    return (q.a.x <= b().x && a.x <= q.b().x) 
		   || q.isLine || isLine;
      	}
      	return 0;
      }
      T t1 = q.ab^(a - q.a);
      T t2 = ab^(q.a - a);
      if (s < 0) t1 = -t1;
      if (s > 0) t2 = -t2;
      bool r1 = (0 <= t1 && t1 <= abs(s)) || isLine;
      bool r2 = (0 <= t2 && t2 <= abs(s)) || q.isLine;
      return r1 && r2;
    }
    double dist(Point<T> p) {
    	if (!isLine) {
    	    if ((p - a) * ab <= 0) return p.dist(a);
	    if ((p - b()) * ab >= 0) return p.dist(b());	
    	}
	return abs((p - a) ^ ab) / ab.norm();
    }
    double dist(Segment p) {
	if (intercept(p)) return 0;
	if (isLine && p.isLine) return abs((ab ^ (p.a - a))) / ab.norm();
	double d1 = min(p.dist(a), p.dist(b()));
	double d2 = min(dist(p.a), dist(p.b()));
	if (isLine) return d2;
	if (p.isLine) return d1;
	return min(d1, d2);
    }
};
