#include "geometric_algorithms.h"
#include <algorithm>
#include <vector>
#include <list>

	#include <iostream>

template <class container, class Iter>
static Iter next(Iter p, const container &c){
	++p;
	if(c.end()==p) p=c.begin();
	return p;
}
template <class container, class Iter>
static Iter prev(Iter p, const container &c){
	if(c.begin() == p) p=c.end();
	return --p;
}

namespace geometry{
	namespace convex_hull{
		typedef std::list<point2d> list;

		template<class Iter>
		Iter rigth_tangent(Iter mid, const point2d &value){
			Iter end = mid;
			++end;
			if( turn_left(value, *mid, *end) ) return mid;

			while( not turn_left(value, *mid, *end) ){
				end = ++mid;
				++end;
			}
			return mid;
		}

		template<class Iter>
		Iter left_tangent(Iter mid, const point2d &value){
			Iter end = mid;
			--end;
			if( not turn_left(value, *mid, *end) ) return mid;

			while( turn_left(value, *mid, *end) ){
				end = --mid;
				--end;
			}
			return mid;
		}

		std::vector<point2d> incremental(std::vector<point2d> points){
			if(points.size()<3) return std::vector<point2d>();
			std::sort(points.begin(), points.end());
			if(not turn_left(points[0], points[1], points[2])) //make sure to store ccw
				std::swap(points[0], points[1]);
			list hull(points.begin(), points.begin()+3);
			hull.push_front(hull.front()); //duplicated endpoints
			list::iterator hint = --hull.end();

			for(size_t K=3; K<points.size(); ++K){
				hull.erase( hull.begin(), rigth_tangent(hull.begin(), points[K]) );
				hull.erase( ++left_tangent(--hull.end(), points[K]), hull.end() );

				hull.push_front(points[K]); //duplicated endpoints
				hull.push_back(points[K]); //duplicated endpoints
			}

			return std::vector<point2d>(hull.begin(), hull.end());
		}

	}
}

