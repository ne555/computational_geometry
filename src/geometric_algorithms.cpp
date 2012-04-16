#include "geometric_algorithms.h"
#include <algorithm>
#include <vector>
#include <utility>
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

	static std::pair<point2d, double> calc_circle(const point2d &a, const point2d &b){
		return std::pair<point2d, double>( (a+b)/2, (a-b).norm_sqr()/4 );
	}
	static std::pair<point2d, double> calc_circle(point2d A, point2d B, point2d C){
		//http://en.wikipedia.org/wiki/Circumscribed_circle#Cartesian_coordinates
		//translation is invariant (simplify calculation)
		B-=A;
		C-=A;
		double determinant = 2*(B[0]*C[1]-B[1]*C[0]);
		point2d center = point2d(
			B.norm_sqr()*C[1]-B[1]*C.norm_sqr(),
			C.norm_sqr()*B[0]-C[0]*B.norm_sqr())/determinant;

		double radious = center.norm_sqr();

		return std::pair<point2d, double>(center+A, radious);
	}
	static bool inside_circle(const point2d &center, double radious, const point2d &p){
		return (center-p).norm_sqr()<=radious;
	}

	std::pair<point2d, double> enclosing_circle(const std::vector<point2d> &v){
		std::pair<point2d, double> circle;
		if(not v.empty()){
			circle.first = v[0];
			circle.second = 0;
		}
		for(size_t K=0; K<v.size(); ++K)
			if(not inside_circle(circle.first, circle.second, v[K])){
				//The circle must pass trough the K point
				circle = calc_circle(v[K], v[0]);
				for(size_t L=0; L<K; ++L)
					if(not inside_circle(circle.first, circle.second, v[L])){
						//The circle must pass trough the K and L points
						circle = calc_circle(v[K], v[L]);
						for(size_t M=0; M<L; ++M){
							if(not inside_circle(circle.first, circle.second, v[M]))
								//The circle must pass trough the K, L and M points
								circle = calc_circle(v[K], v[L], v[M]);
						}
					}
			}

		circle.second = sqrt(circle.second); //work with the square radious as long as possible
		return circle;
	}
}

