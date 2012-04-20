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
		//The cpp has explicit instantiation of these methods
			template<class container>
				bool add(container &c, const point2d&);
			template<class container, class iterator>
				iterator before(container &c, iterator it);
			template<class container, class iterator>
				iterator after(container &c, iterator it);
		public:
			template<class container>
				container add_return_mia(container &c, const point2d&);
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

		class onion{
		public:
			std::vector<online> layers;
			void add(const point2d &);
			template<class F>
			void apply(F func) const{
				for(size_t K=0; K<layers.size(); ++K)
					layers[K].apply(func);
			}
		};
		std::vector<point2d> incremental(std::vector<point2d>);
		std::vector< std::vector<point2d> > onion_layers(std::vector<point2d> points);
	}
}

#endif 

