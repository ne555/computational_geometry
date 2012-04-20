/* Pick points */
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "point.h"
#include "geometric_algorithms.h"
namespace gm = geometry;

void Display_cb();
void Reshape_cb(int width, int height);
void Motion_cb(int x, int y);
void Mouse_cb(int button, int state, int x, int y);
void Keyboard_cb(unsigned char key,int x,int y);
void Special_cb(int key,int xm=0,int ym=0);
void initialize();

/* Evil globals */
int w=500,h=500;
float ew=1.0/w, eh=1.0/h;
int index=0;
typedef std::vector<gm::point2d> point_list;
point_list points;
void draw_point(const gm::point2d &p){
	glVertex2dv(p.data());
}

gm::convex_hull::online hull;

int main(int argc,char** argv) {
	glutInit(&argc,argv);
	initialize();
	glutMainLoop();
	return 0;
}

void Display_cb() {
	glClear(GL_COLOR_BUFFER_BIT);


	glLineWidth(1);
	glColor3f(1,0,0);
	glBegin(GL_LINE_STRIP);{
		hull.apply( draw_point );
	};glEnd();

	glPointSize(4);
	glColor3f(0,0,0);
	glBegin(GL_POINTS);{
		for(size_t K=0; K<points.size(); ++K)
			draw_point(points[K]);
	};glEnd();
	std::cerr << points.size() << ' ';

	
	glutSwapBuffers(); 
}

void Reshape_cb(int width, int height){
	if (!width||!height) return; 
	w=width; h=height;
	glViewport(0,0,w,h); 
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	if(w<=h)
		glOrtho(0,1,0,float(h)/w,-1,1);
	else
		glOrtho(0,float(w)/h,0,1,-1,1);
	ew = 1.0/std::min(h,w);
	eh = 1.0/std::min(h,w);
	
	glutPostRedisplay();
}

void Motion_cb(int xw, int yw){
	double x = double(xw)*ew, y = double(h-yw)*eh;
	points[index] = gm::point2d(x,y);
	glutPostRedisplay();
}

void Mouse_cb(int button, int state, int xw, int yw){
	double x = double(xw)*ew, y = double(h-yw)*eh;
	if(state == GLUT_DOWN){
	/*
		double tol = 0.01;
		gm::point2d pick(x,y);
		index = gm::nearest(points.begin(), points.end(), pick)-points.begin();
		if(points.empty() or gm::manhatan_distance(points[index], pick)>tol ){
			index = points.size();
			points.push_back(pick);
		}
	*/
		gm::point2d pick(x,y);
		points.push_back(pick);
		if( hull.add(pick) )
			std::cout << "Hull" << std::endl;
		else
			std::cout << "Inside" << std::endl;
	}

	glutPostRedisplay();
}

void Keyboard_cb(unsigned char key,int x,int y) {
	switch(key){
	case 'q': exit(EXIT_SUCCESS);
	}
}

void Special_cb(int key,int xm,int ym) {
}

void initialize() {
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(w,h); glutInitWindowPosition(50,50);
	glutCreateWindow("convex_hull"); 
	glutDisplayFunc(Display_cb);
	glutReshapeFunc(Reshape_cb);
	glutKeyboardFunc(Keyboard_cb);
	glutSpecialFunc(Special_cb);
	glutMouseFunc(Mouse_cb);
	glutMotionFunc(Motion_cb);
	glClearColor(1,1,1,1); 
	glMatrixMode(GL_MODELVIEW); glLoadIdentity(); 

	glColor3f(0,0,0);
}

