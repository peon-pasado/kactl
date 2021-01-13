/**
 * Author: Ulf Lundstrom with inspiration from tinyKACTL
 * Date: 2009-04-14
 * License: CC0
 * Source:
 * Description: Class to handle points in 3D space.
 * 	T can be e.g. double or long long.
 * Usage:
 * Status: tested, except for phi and theta
 */
#pragma once

template<class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
	bool operator<(R p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z); }
	bool operator==(R p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z); }
	P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const { return P(x*d, y*d, z*d); }
	P operator/(T d) const { return P(x/d, y/d, z/d); }
	T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const {
		return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
	T dist2() const { return x*x + y*y + z*z; }
	double dist() const { return sqrt((double)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	double phi() const { return atan2(y, x); } 
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	double theta() const { return atan2(sqrt(x*x+y*y),z); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
	//returns point rotated 'angle' radians ccw around axis
	P rotate(double angle, P axis) const {
		double s = sin(angle), c = cos(angle); P u = axis.unit();
		return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
	}
};


Matrix translate(Point p) { //T(u) = u + p 
  Matrix R;
  R.one();
  R.mat[0][3] = p.x;
  R.mat[1][3] = p.y;
  R.mat[2][3] = p.z;
  return R;
}

Matrix scale(Point p) { //T(u) = (p.x * u, p.y * u, p.z * u)
  Matrix R;
  R.mat[0][0] = p.x;
  R.mat[1][1] = p.y;
  R.mat[2][2] = p.z;
  R.mat[3][3] = 1;
  return R;
}

Matrix rotate(Point p, double alpha) { //rotate alpha counterclockwise through vector p
  Matrix W;
  p = p.unit();
  W.mat[0][1] = -p.z;
  W.mat[0][2] = p.y;
  W.mat[1][0] = p.z;
  W.mat[1][2] = -p.x;
  W.mat[2][0] = -p.y;
  W.mat[2][1] = p.x;
  Matrix R;
  R.one();
  R.mat[3][3] = 0;
  R = R + sin(alpha) * W + (1 - cos(alpha)) * W * W;
  R.mat[3][3] = 1;
  return R;
}



