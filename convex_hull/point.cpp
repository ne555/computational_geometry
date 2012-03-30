#include "point.h"
#include <cmath>

namespace geometry{
	point2d::point2d():x(2){}
	point2d::point2d(double x, double y): x(2){
		this->x[0] = x;
		this->x[1] = y;
	}
	const point2d::value_type* point2d::data() const{
		return &x[0];
	}
	point2d::value_type* point2d::data(){
		return &x[0];
	}

	point2d::value_type point2d::norm_max() const{
		return abs(x).max();
	}
	point2d::value_type point2d::norm_sqr() const{
		return (x*x).sum();
	}

	point2d::value_type manhatan_distance(const point2d &a, const point2d &b){
		return (a-b).norm_max();
	}

	point2d& point2d::operator+=(const point2d &b){
		x+=b.x;
		return *this;
	}
	point2d& point2d::operator-=(const point2d &b){
		x-=b.x;
		return *this;
	}
	point2d& point2d::operator*=(value_type f){
		x*=f;
		return *this;
	}
	point2d& point2d::operator/=(value_type f){
		x/=f;
		return *this;
	}
	point2d operator+(const point2d &left, const point2d &right){
		point2d result(left);
		return result+=right;
	}
	point2d operator-(const point2d &left, const point2d &right){
		point2d result(left);
		return result-=right;
	}
	point2d operator/(const point2d &left, point2d::value_type right){
		point2d result(left);
		return result/=right;
	}
	point2d operator*(const point2d &left, point2d::value_type right){
		point2d result(left);
		return result*=right;
	}
	point2d operator/(point2d::value_type left, const point2d &right){
		return right/left;
	}
	point2d operator*(point2d::value_type &left, const point2d &right){
		return right*left;
	}

	point2d::value_type point2d::operator*(const point2d &b) const{ //inner product
		return (x*b.x).sum();
	}
	point2d::value_type point2d::operator%(const point2d &b) const{ //cross product (z coord)
		/*
			\left|
				\begin{array}{ccc}
					i & j & k \\
					a.x & a.y & 0 \\
					b.x & b.y & 0 \\
				\end{array}
			\right|
		*/
		return x[0]*b.x[1] - x[1]*b.x[0];
	}
	//triangle area( point2d a,b,c ){
		/*
			\left|
				\begin{array}{ccc}
					1 & a.x & a.y \\
					1 & b.x & b.y \\
					1 & c.x & c.y \\
				\end{array}
			\right|
		*/
	//}

	bool point2d::operator<(const point2d &b) const{ //coordinate
		for(size_t K=0; K<x.size(); ++K)
			if(x[K]<b.x[K])
				return true;
			else if(b.x[K]<x[K])
				return false;
		return false;
	}
}

