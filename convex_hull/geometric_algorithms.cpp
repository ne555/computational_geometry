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
			hull.push_front(points[2]); //duplicated endpoints

			for(size_t K=3; K<points.size(); ++K){
				list::iterator 
					r = rigth_tangent(hull.begin(), points[K]),
					l = left_tangent(--hull.end(), points[K]);
				++l;

				hull.erase(hull.begin(), r);
				if(l!=hull.end())
				hull.erase(l, hull.end());

				hull.push_front(points[K]); //duplicated endpoints
				hull.push_back(points[K]); //duplicated endpoints
			}

			return std::vector<point2d>(++hull.begin(), hull.end());
		}

		std::vector< std::vector<point2d> > onion_layers(std::vector<point2d> points){
			if(points.size()<3) return std::vector< std::vector<point2d> >();
			std::sort(points.begin(), points.end());

			std::vector<bool> in_here(points.size(),false);
			std::vector< std::vector<point2d> > onion;
			//while( not points.empty() ){
			while(points.size()>=3){
				if(not turn_left(points[0], points[1], points[2])) //make sure to store ccw
					std::swap(points[0], points[1]);
				list layer(points.begin(),points.begin()+3);
				layer.push_front(points[2]); //duplicated endpoints

				std::vector<bool> in_hull(points.size(),false);
				in_hull[0] = in_hull[1] = in_hull[2] = true;

				//get an increment
				for(size_t K=3; K<points.size(); ++K){
					list::iterator 
						r = rigth_tangent(layer.begin(), points[K]),
						l = left_tangent(--layer.end(), points[K]);
					++l;

					layer.erase(layer.begin(), r);
					if(l!=layer.end())
					layer.erase(l, layer.end());

					layer.push_front(points[K]); //duplicated endpoints
					layer.push_back(points[K]); //duplicated endpoints
				}
				layer.pop_front();

				//delete the used points
				for(list::iterator it=layer.begin(); it!=layer.end(); ++it)
					points.erase( std::find(points.begin(), points.end(), *it) );
				

				onion.push_back( std::vector<point2d>(layer.begin(), layer.end()) );
			}
			return onion;
		}

	}
}

