#include "point.h"

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
}

