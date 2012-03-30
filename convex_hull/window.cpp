/* Pick points */
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "point.h"
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
std::vector<gm::point2d> points;

int main(int argc,char** argv) {
	glutInit(&argc,argv);
	initialize();
	glutMainLoop();
	return 0;
}

void Display_cb() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);{
		for(size_t K=0; K<points.size(); ++K)
			glVertex2dv(points[K].data());
	};glEnd();

	glBegin(GL_LINE_LOOP);{
		for(size_t K=0; K<points.size(); ++K)
			glVertex2dv(points[K].data());
	};glEnd();
	
	glutSwapBuffers(); 
}

void Reshape_cb(int width, int height){
	if (!width||!height) return; 
	w=width; h=height;
	glViewport(0,0,w,h); 
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	glOrtho(0,1,0,1,-1,1);
	glutPostRedisplay();
}

void Motion_cb(int x, int y){
}

void Mouse_cb(int button, int state, int xw, int yw){
	double x = double(xw)/w, y = double(h-yw)/h;
	if(state == GLUT_DOWN)
		points.push_back( gm::point2d(x,y) );

	std::cerr << x << ' ' << y << '\t';
	glutPostRedisplay();
}

void Keyboard_cb(unsigned char key,int x,int y) {
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
	glClearColor(0.85f,0.9f,0.95f,1.f); 
	glMatrixMode(GL_MODELVIEW); glLoadIdentity(); 

	glColor3f(0,0,0);
}

