#include<GL/glut.h>	
#include<stdlib.h>



void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	//glViewport(0, 0, 400, 400);
}

void draw_quare() {
	glBegin(GL_POLYGON);

	glVertex2f(-0.5 ,- 0.5);

	glVertex2f(-0.5, 0.5);

	glVertex2f(0.5, 0.5);

	glVertex2f(0.5, -0.5);

	glEnd();

}



void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();



	//���������� �� View port�� ���ǥ��
	glViewport(0, 0, 400, 400);

	glColor3f(1.0, 0.0, 0.0);



	glBegin(GL_LINES);

	glVertex2f(-1.0, 0.0);

	glVertex2f(1.0, 0);

	glVertex2f(0.0, -1.0);

	glVertex2f(0.0, 1.0);

	glEnd();



	//���ϴ� �κ��� viewport, ��� �簢��

	glViewport(0, 0, 200, 200);

	glColor3f(0.0, 1.0, 0.0);

	draw_quare();



	//�»�� �κ�, ��ũ

	glViewport(0, 200, 200, 200);

	glColor3f(1.0, 0.0, 1.0);

	draw_quare();



	//���ϴ�, ���

	glViewport(200, 0, 200, 200);

	glColor3f(1.0, 1.0, 0.0);

	draw_quare();

}


int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Transformed Cube");

	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}



