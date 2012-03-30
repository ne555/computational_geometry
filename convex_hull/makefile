cxx = g++
cppflags = -Wall -pedantic-errors -O2
libraries = -l{GL,GLU,glut}
libraries = $(addprefix -l,GL GLU glut)
project = convex_hull.bin

objects = window.o

$(project) : $(objects)
	$(cxx) $(cppflags) $(libraries) $(objects) -o $@

#%.o : %.cpp
#	$(CXX) $< -c $(CPPFLAGS) -o $@

.PHONY: clean

clean:
	-rm $(objects) $(project)

