cxx = g++
cppflags = -Wall -pedantic-errors -ggdb
#cppflags = -Wall -pedantic-errors -O2
libraries = $(addprefix -l,GL GLU glut)
projects = convex_hull.bin minimal_circle.bin

ch_objects = $(addprefix obj/, convex_hull.o point.o geometric_algorithms.o)
mec_objects = $(addprefix obj/, minimal_circle.o point.o geometric_algorithms.o)

all: $(projects)

convex_hull.bin : $(ch_objects)
	$(cxx) $(cppflags) $(libraries) $(ch_objects) -o $@

minimal_circle.bin : $(mec_objects)
	$(cxx) $(cppflags) $(libraries) $(mec_objects) -o $@

obj/convex_hull.o: $(addprefix header/, point.h geometric_algorithms.h)
obj/minimal_circle.o: $(addprefix header/, point.h geometric_algorithms.h)
obj/point.o: $(addprefix header/, point.h)
obj/geometric_algorithms.o: $(addprefix header/, point.h geometric_algorithms.h)

obj/%.o: src/%.cpp
	$(cxx) $< -c $(cppflags) -Iheader -o $@

.PHONY: clean 

clean:
	-rm $(mec_objects) 
	-rm $(ch_objects)
	-rm $(projects)


