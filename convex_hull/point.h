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

		value_type norm_max() const;
		value_type norm_sqr() const;

		//operators
		point2d& operator+=(const point2d&);
		point2d& operator-=(const point2d&);
		point2d& operator*=(value_type);
		point2d& operator/=(value_type);
	};

	point2d::value_type manhatan_distance(const point2d &a, const point2d &b);
	point2d operator+(const point2d &left, const point2d &right);
	point2d operator-(const point2d &left, const point2d &right);
	point2d operator/(const point2d &left, point2d::value_type right);
	point2d operator*(const point2d &left, point2d::value_type right);
	point2d operator/(point2d::value_type left, const point2d &right);
	point2d operator*(point2d::value_type &left, const point2d &right);
}

#endif

