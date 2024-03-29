/*
Date: 2022.03.23.
*/

#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>

#define size 50.0

float w_height = 800;
float w_width = 800;
float square_x = 0, square_y = 400;
float square_dx = 0.1, square_dy = 0.1;

void idleCallBack() {
	square_x += square_dx;
	square_y += square_dy;
	if (square_x + size > w_width || square_x <= 0 ||
		square_y + size > w_height || square_y <= 0) {
		square_dx *= -1.0;
		square_dy *= -1.0;
	}

	// 자동으로 display func 호출
	glutPostRedisplay();
}

void displayCallBack() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // 처음에 단위행렬 호출 => 초기화
	glOrtho(0.0, w_width, 0.0, w_height, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(square_x, square_y, 0.0);

	glColor3ub(255, 255, 0);
	glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(size, 0);
		glVertex2f(size, size);
		glVertex2f(0, size);
	glEnd();

	//Double buffer = glutSwapBuffers()
	//Single Buffer = glFlush()
	glutSwapBuffers();
}

int main(int argc, char ** argv) {
	glutInit(&argc, argv);

	glutInitWindowPosition(10, 10);
	glutInitWindowSize(w_width, w_height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Idle Callback");

	glutDisplayFunc(displayCallBack);
	glutIdleFunc(idleCallBack);

	glutMainLoop();
	return 0;
}