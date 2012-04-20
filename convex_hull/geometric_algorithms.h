#ifndef GEOM_ALGO_H
#define GEOM_ALGO_H

#include "point.h"
#include <vector>
#include <utility>
#include <set>
#include <functional>

namespace geometry{
	template <class Iter>
	Iter nearest(Iter beg, Iter end, const point2d &value){
		Iter result = beg;
		for(; beg!=end; ++beg)
			if( manhatan_distance(*beg, value) < manhatan_distance(*result, value) )
				result = beg;
		return result;
	}
	namespace convex_hull{
		class online{
		private:
		//The cpp has explicit instantiation of this method
			template<class container>
			bool add(container &c, const point2d&);
		public:
			//ccw
			std::set<point2d> lower;
			std::set<point2d, std::greater<point2d> > upper;
			bool add(const point2d &);
			template <class F>
			void apply(F func) const{
				typedef std::set<point2d>::const_iterator lcit;
				typedef std::set<point2d, std::greater<point2d> >::const_iterator ucit;
				for(lcit it=lower.begin(); it!=lower.end(); ++it)
					func(*it);
				for(ucit it=upper.begin(); it!=upper.end(); ++it)
					func(*it);
			}
		};
		std::vector<point2d> incremental(std::vector<point2d>);
		std::vector< std::vector<point2d> > onion_layers(std::vector<point2d> points);
	}
}

#endif 

