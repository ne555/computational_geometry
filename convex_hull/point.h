#ifndef POINT_H
#define POINT_H
#include <valarray>

	#include <iostream>

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

		point2d::value_type operator*(const point2d &b) const; //inner product
		point2d::value_type operator%(const point2d &b) const; //cross product (z coord)

		bool operator<(const point2d &b) const; //coordinate
		bool operator==(const point2d &b) const;

		void print(std::ostream &out) const;
	};

	point2d::value_type manhatan_distance(const point2d &a, const point2d &b);
	point2d operator+(const point2d &left, const point2d &right);
	point2d operator-(const point2d &left, const point2d &right);
	point2d operator/(const point2d &left, point2d::value_type right);
	point2d operator*(const point2d &left, point2d::value_type right);
	point2d operator/(point2d::value_type left, const point2d &right);
	point2d operator*(point2d::value_type &left, const point2d &right);

	bool turn_left(const point2d &beg, const point2d &mid, const point2d &end);

}

#endif

