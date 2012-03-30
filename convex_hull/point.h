#ifndef POINT_H
#define POINT_H
#include <valarray>

namespace geometry{
	class point2d{
	public:
		typedef double value_type;
		typedef std::valarray<value_type> vector;
		vector x;
		//point(size_t n);
		point2d();
		point2d(double x, double y);
		const value_type* data() const;
		value_type* data();
	};
}

#endif

