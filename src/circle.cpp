#include "circle.h"
#include "line.h"

	#include <iostream>

namespace geometry{
	circle::circle(const point2d &c, double radious):
		center(c), 
		radious_sqr(radious*radious){}

	circle::circle(const point2d &a, point2d &b):
		center((a+b)/2), 
		radious_sqr((a-b).norm_sqr()/4 ){}

	circle::circle(point2d a, point2d b, point2d c){
		//http://en.wikipedia.org/wiki/Circumscribed_circle#Cartesian_coordinates
		//translation is invariant (simplify formulae)
		b-=a;
		c-=a;
		double determinant = 2*(b[0]*c[1]-b[1]*c[0]);
		center = point2d(
				b.norm_sqr()*c[1]-b[1]*c.norm_sqr(),
				c.norm_sqr()*b[0]-c[0]*b.norm_sqr())/determinant;

		radious_sqr = center.norm_sqr();
	}

	bool circle::inside(const point2d &p) const{
		return (center-p).norm_sqr() <= radious_sqr;
	}

	point2d circle::intersection(const line &l) const{
		double to_center = l.distance(center);
		double other = std::sqrt(radious_sqr-to_center*to_center);

		return l.projection(center) + other*l.direction;
	}
}

