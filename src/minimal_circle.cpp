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
void draw_circle(const gm::point2d& c, const double& r, int lod=32);

/* Evil globals */
int w=500,h=500;
float ew=1.0/w, eh=1.0/h;
int index=0;
typedef std::vector<gm::point2d> point_list;
point_list points;

int main(int argc,char** argv) {
	glutInit(&argc,argv);
	initialize();
	size_t n=1e4;
	for(size_t K=0; K<n; ++K){
		double x = rand()/double(RAND_MAX);
		double y = rand()/double(RAND_MAX);
		gm::point2d base(0.5, 0.5);
		points.push_back(base+gm::point2d(x,y)/4);
	}
	gm::enclosing_circle(points).first.print(std::cerr);
	glutMainLoop();
	return 0;
}

void Display_cb() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0,0,0);
	glPointSize(4);
	glBegin(GL_POINTS);{
		for(size_t K=0; K<points.size(); ++K)
			glVertex2dv(points[K].data());
	};glEnd();

	if(not points.empty()){
		std::pair<gm::point2d, double> circle = gm::enclosing_circle(points);
		glLineWidth(1);
		glColor3f(1,0,0);
		draw_circle(circle.first, circle.second);
		circle.first.print(std::cerr);
		std::cerr << circle.second << ' ';
	}
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
		double tol = 0.01;
		gm::point2d pick(x,y);
		index = gm::nearest(points.begin(), points.end(), pick)-points.begin();
		if(points.empty() or gm::manhatan_distance(points[index], pick)>tol ){
			index = points.size();
			points.push_back(pick);
		}
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

void draw_circle(const gm::point2d& c, const double& r, int lod){
	static const float R22=sqrt(2.f)/2;
	static const float 
		pc[9*4]={
			0  ,  -1, 0,  1,
				R22,-R22, 0,R22,
				1  ,   0, 0,  1,
				R22, R22, 0,R22,
				0  ,   1, 0,  1,
				-R22, R22, 0,R22,
				-1  ,   0, 0,  1,
				-R22,-R22, 0,R22,
				0  ,  -1, 0,  1}, knots[12]={0,0,0,1,1,2,2,3,3,4,4,4};
	static GLUnurbsObj* circ=gluNewNurbsRenderer();
	gluNurbsProperty(circ,GLU_SAMPLING_METHOD,GLU_DOMAIN_DISTANCE); // para usar lod
	gluNurbsProperty(circ,GLU_U_STEP,float(lod));
	gluNurbsProperty(circ,GLU_DISPLAY_MODE,GLU_FILL);
	glPushMatrix();
	glTranslated(c[0],c[1],0);
	glScaled(r,r,1);
	gluBeginCurve(circ);
	gluNurbsCurve(circ,12,(float *)knots,4,(float *)pc,3,GL_MAP1_VERTEX_4);
	gluEndCurve(circ);
	glPopMatrix();
}
