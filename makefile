cxx = g++
cppflags = -Wall -pedantic-errors -ggdb
libraries = $(addprefix -l,GL GLU glut)
project = convex_hull.bin

objects = $(addprefix obj/, convex_hull.o point.o geometric_algorithms.o)

$(project) : $(objects)
	$(cxx) $(cppflags) $(libraries) $(objects) -o $@

obj/point.o: $(addprefix header/, point.h)
obj/convex_hull.o: $(addprefix header/, point.h geometric_algorithms.h)
obj/geometric_algorithms.o: $(addprefix header/, point.h geometric_algorithms.h)

obj/%.o: src/%.cpp
	@$(cxx) $< -c $(cppflags) -Iheader -o $@

.PHONY: clean test

clean:
	-rm $(objects) $(project)

test: $(project)
	./$(project)

