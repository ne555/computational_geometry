#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"
namespace geometry{
	class line;
	class circle{
	public:
		point2d center;
		double radious_sqr;

		circle(const point2d &c, double radious);
		circle(const point2d &a, point2d &b); 
		circle(point2d a, point2d b, point2d c);

		bool inside(const point2d &) const;
		bool intersects(const line &) const;
		/* make sure that they intersect before call it */
		// as the line is directed, to find the other intersection invert it 
		point2d intersection(const line &) const;
	};
}

#endif

