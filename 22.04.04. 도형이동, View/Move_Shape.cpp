#include<GL/glut.h>
#include<stdlib.h>

float v1[3] = { -10.0,-35.0,0.0 };
float v2[3] = { 10.0,-35.0,0.0 };
float v3[3] = { 10.0,35.0,0.0 };
float v4[3] = { -10.0,35.0,0.0 };


void init() {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0, 400.0, -100.0, 400.0);

}

//»ç°¢Çü
void draw_square() {

	glBegin(GL_POLYGON);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glEnd();

}



void draw_line() {

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-100.0, 0.0, 0.0);
	glVertex3f(400.0, 0.0, 0.0);
	glVertex3f(0.0, -100.0, 0.0);
	glVertex3f(0.0, 400.0, 0.0);
	glEnd();

}



void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	draw_line();
	glColor3f(0.0, 0.0, 1.0);
	draw_square();

	//Rotate 45 degree and then translate 100 to x direction
	glLoadIdentity();
	glTranslatef(100.0, 0.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 0.);
	draw_square();

	glLoadIdentity();
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(100.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	draw_square();

	glFlush();

}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Object Transformation Program");

	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;

}