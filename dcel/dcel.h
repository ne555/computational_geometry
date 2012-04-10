#ifndef DCEL_H
#define DCEL_H

namespace geometry{
	class node;
	class edge;
	class face;

	class node{
		point coordinate;
		edge *incidend;
	};
	class edge{ //semi-edge actually
		node *origin;
		edge *next, *previous, *twin;
		face *inner;
	};
	class face{ //ghost edges for holes
		edge *boundary;	
		/*attributtes*/
	};
}

#endif

