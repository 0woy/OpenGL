#include<GL/glut.h>

void draw_square() {
	glBegin(GL_POLYGON);
	glVertex2f(-0.2, 0.2);
	glVertex2f(-0.2, -0.2);
	glVertex2f(0.2, -0.2);
	glVertex2f(0.2, 0.2);
	glEnd();
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);		//RED
	draw_square();

	glPushMatrix();

	glColor3f(0.0, 1.0, 0.0);		// GREEN
	glTranslatef(-0.6, 0.6, 0.0);
	draw_square();

	glPopMatrix();	// CTM = I*T1 날아감. (CTM = I)
	glPushMatrix(); // CTM = I, I: push

	glColor3f(0.0, 0.0, 1.0);	// BLUE, R -> T
	glTranslatef(0.6, 0.6, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	draw_square();


	glColor3f(1.0, 0.0, 1.0);	//PINK
	glScalef(1.2, 1.2, 1.0);
	glTranslatef(-0.7, -0.7, 0.0);	// blue에서 축이 45도 회전
	draw_square();					// 따라서 우측 하단에 그려지는 것임. 중요!!!

	glPopMatrix();	// CMT = I*R*T1*T2*S 삭제 (CMT = I)

	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(-0.6, -0.6, 0.0);
	glScalef(1.2, 1.2, 1.0);
	draw_square();

	glFlush();
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	glViewport(0, 0, 400, 400);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);	//GLUT 상태를 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);


	glutCreateWindow("Push Pop Matrix");
	glutDisplayFunc(display);
	init();

	glutMainLoop();

	return 0;
}