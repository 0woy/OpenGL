#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>

float y_position;
bool flag;


void init() {
	y_position = 0;
	flag = false;
}

void draw_axis() {
	glColor3f(1.0, 1.0, 0.0);
	
	glBegin(GL_LINES);
	glVertex2f(-1.0, 0.0);
	glVertex2f(11.0, 0.0);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 11.0);
	glEnd();

}

void draw_basic_axis_line() {

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex2f(0.0, y_position);
	glVertex2f(10.0, y_position);
	glEnd();
}

void draw_triangle() {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(5.0, 6.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(4.0, 4.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(6.0, 4.0);
	glEnd();
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_axis();
	draw_basic_axis_line();

	if (flag) {
		glTranslatef(5.0, y_position, 0.0); //좌표변환
		glRotatef(180.0, 1.0, 0.0, 0.0); //180도 회전
		glTranslatef(-5.0, -y_position, 0.0);

	}
	draw_triangle();

	glFlush();

}


void keyboard(unsigned char key, int x, int y) {

	switch (key)
	{
	case 'r':
		flag = true;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void SpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		y_position += 0.1;
		glutPostRedisplay();
		flag = false;
	}
	if (key == GLUT_KEY_DOWN) {
		y_position -= 0.1;
		glutPostRedisplay();
		flag = false;
	}
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 11.0, -1.0, 11.0, -1.0, 1.0);
	glShadeModel(GL_SMOOTH);
}



int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Axis-based Rotation");

	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutSpecialFunc(SpecialKeys);
	glutMainLoop();

	return 0;
}