cxx = g++
#cppflags = -Wall -pedantic-errors -ggdb
cppflags = -Wall -pedantic-errors -O2
libraries = -l{GL,GLU,glut}
libraries = $(addprefix -l,GL GLU glut)
project = convex_hull.bin

objects = window.o point.o geometric_algorithms.o

$(project) : $(objects)
	$(cxx) $(cppflags) $(libraries) $(objects) -o $@

point.o: point.h
window.o: point.h geometric_algorithms.h
geometric_algorithms.o: point.h geometric_algorithms.h

%.o : %.cpp
	$(cxx) $< -c $(cppflags) -o $@

.PHONY: clean test

clean:
	-rm $(objects) $(project)

test: $(project)
	./$(project)

