cxx = g++
cppflags = -Wall -pedantic-errors -ggdb
libraries = $(addprefix -l,GL GLU glut)
projects = convex_hull.bin

ch_objects = $(addprefix obj/, convex_hull.o point.o geometric_algorithms.o)

all: $(projects)

convex_hull.bin : $(ch_objects)
	$(cxx) $(cppflags) $(libraries) $(ch_objects) -o $@

obj/convex_hull.o: $(addprefix header/, point.h geometric_algorithms.h)
obj/point.o: $(addprefix header/, point.h)
obj/geometric_algorithms.o: $(addprefix header/, point.h geometric_algorithms.h)

obj/%.o: src/%.cpp
	@$(cxx) $< -c $(cppflags) -Iheader -o $@

.PHONY: clean 

clean:
	-rm $(ch_objects) $(projects)


