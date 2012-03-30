#include "geometric_algorithms.h"
#include <algorithm>
#include <vector>

namespace geometry{
	namespace convex_hull{
		std::vector<point2d> incremental(std::vector<point2d> points){
			if(points.size()<3) return std::vector<point2d>();
			std::sort(points.begin(), points.end());
			std::list<point2d> hull(points.begin(), points.begin()+3);
			for(size_t K=3; K<points.size(); ++K){
				
			}

			return std::vector<point2d>(hull.begin(), hull.end());
		}
	}
}

