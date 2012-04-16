#ifndef LINE_H
#define LINE_H
namespace geometry{
	class line{
		point beg, end;
		point intersection(const line &b) const;
	};
}

#endif

