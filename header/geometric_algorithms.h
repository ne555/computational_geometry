#ifndef GEOM_ALGO_H
#define GEOM_ALGO_H

#include "point.h"
#include "circle.h"
#include <vector>
#include <utility>

namespace geometry{
	class line;
	class circle;
	template <class Iter>
	Iter nearest(Iter beg, Iter end, const point2d &value){
		Iter result = beg;
		for(; beg!=end; ++beg)
			if( manhatan_distance(*beg, value) < manhatan_distance(*result, value) )
				result = beg;
		return result;
	}
	namespace convex_hull{
		std::vector<point2d> incremental(std::vector<point2d>);
		std::vector< std::vector<point2d> > onion_layers(std::vector<point2d> points);
	}

	circle enclosing_circle(const std::vector<point2d>&);

}

#endif 

