cxx = g++
cppflags = -Wall -pedantic-errors -O2
libraries = -l{GL,GLU,glut}
libraries = $(addprefix -l,GL GLU glut)
project = convex_hull.bin

objects = window.o point.o

$(project) : $(objects)
	$(cxx) $(cppflags) $(libraries) $(objects) -o $@

point.o: point.h
window.o: point.h geometric_algorithms.h
#%.o : %.cpp
#	$(CXX) $< -c $(CPPFLAGS) -o $@

.PHONY: clean test

clean:
	-rm $(objects) $(project)

test: $(project)
	./$(project)

