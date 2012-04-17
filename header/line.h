#ifndef LINE_H
#define LINE_H
#include "point.h"
namespace geometry{
	class line{ //actually half-line
	public:
		point2d start, direction;
	public:
		line();
		line(const point2d &start, const point2d &direction);
		double distance(const point2d &) const;

		point2d point(double time) const;
		point2d projection(const point2d &) const;
		line ccw_ort() const;
	};
}

#endif
