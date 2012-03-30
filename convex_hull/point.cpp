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
}

