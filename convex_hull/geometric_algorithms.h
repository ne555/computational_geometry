#include "point.h"

#ifndef GEOM_ALGO_H
#define GEOM_ALGO_H

namespace geometry{
	template <class Iter>
	Iter nearest(Iter beg, Iter end, const point2d &value){
		Iter result = beg;
		for(; beg!=end; ++beg)
			if( manhatan_distance(*beg, value) < manhatan_distance(*result, value) )
				result = beg;
		return result;
	}
}

#endif 

