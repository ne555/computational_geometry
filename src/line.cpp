#include "line.h"
#include <cmath>

namespace geometry{
	line::line():start(), direction(1,0){}	
	line::line(const point2d &start, const point2d &direction):
		start(start),
		direction(direction.normalized()){}

	double line::distance(const point2d &p) const{
		return (p-start)%direction;
	}

	point2d line::point(double time) const{
		return start+time*direction;
	}
	line line::ccw_ort() const{
		return line(start, direction.ccw_ort());
	}

	point2d line::projection(const point2d &p) const{
		return point( (p-start)*direction );
	}
}
