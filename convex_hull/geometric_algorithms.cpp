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

		bool online::add(const point2d &p){
		//suppose that the point form part of either hull;
			bool low=add(lower, p), up=add(upper, p);
			return low or up;
		}

		template<class container>
		bool online::add(container &c, const point2d &p){
			typedef typename container::iterator iterator;
			iterator it = c.insert(p).first;
			if(c.size()==1 or c.size()==2) return true;
			//std::set<point2d, std::greater<point2d> >::iterator uit = upper.insert(p).first;
		//if we are correct, then there must be a ccw turn (left)
			if( it not_eq c.begin() and it not_eq --c.end() ){ //special case, the extremes we are sure there are fine
				iterator prev = it, next = it;
				--prev; ++next;
				if( not turn_left(*prev, *it, *next) ){ //crap, we were wrong
					c.erase(it); //let everything as it was
					return false; //we did nothing
				}
			}
			//now we need to kill the bad neighbours
			iterator before=this->before(c,it), after=this->after(c,it);
			if(before not_eq it)
				c.erase(before, it);
			if(after not_eq it)
				c.erase(++it, ++after);
			return true;
		}

		template<class container, class iterator>
		iterator online::before(container &c, iterator it){
			if(it == c.begin())
				return it;
			iterator mid = it, first;
			first = --mid; --first;
			while(mid not_eq c.begin()){
				if( turn_left(*first, *mid, *it) ) break;
				first = --mid; --first;
			}
			return ++mid;
		}
		template<class container, class iterator>
		iterator online::after(container &c, iterator it){
			if(it == --c.end()) 
				return it;
			iterator mid = it, last;
			last = ++mid; ++last;
			while(last not_eq c.end()){
				if( turn_left(*it, *mid, *last) ) break;
				last = ++mid; ++last;
			}
			return --mid;
		}


		//explicit instantiation
		template bool online::add(std::set<point2d>&, const point2d&);
		template bool online::add(std::set<point2d, std::greater<point2d> >&, const point2d&);

		template std::set<point2d>::iterator 
			online::before(std::set<point2d> &c, std::set<point2d>::iterator it);
		template std::set<point2d, std::greater<point2d> >::iterator 
			online::before(std::set<point2d, std::greater<point2d> > &c, std::set<point2d>::iterator it);
		template std::set<point2d>::iterator 
			online::after(std::set<point2d> &c, std::set<point2d>::iterator it);
		template std::set<point2d, std::greater<point2d> >::iterator 
			online::after(std::set<point2d, std::greater<point2d> > &c, std::set<point2d>::iterator it);
	}
}

