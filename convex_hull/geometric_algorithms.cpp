#include "geometric_algorithms.h"
#include <algorithm>
#include <vector>

namespace geometry{
	namespace convex_hull{
		std::vector<point2d> incremental(std::vector<point2d> points){
			std::sort(points.begin(), points.end());
		}
	}
}

