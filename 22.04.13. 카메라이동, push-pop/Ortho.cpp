#include<GL/glut.h>
#include<stdlib.h>


void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glColor3f(1.0, 0.0, 0.0); //RED	
	glutWireCube(1.0);

	glPushMatrix();

	glColor3f(0.0, 1.0, 0.0); //GREEN
	glTranslatef(-1.5, 0.0, 1.5); //물체 이동에 따른 변화 확인
	glutWireCube(1.0);

	glPopMatrix();

	glColor3f(0.0, 0.0, 1.0);	//blue
	glTranslatef(1.5, 0.0, 1.5);	//물체의 이동에 따른 변화 확인
	glutWireCube(1.0);

	glFlush();

}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);	//원근 투영
	//glOrtho(-7.0, 7.0, -7.0, 7.0, 1.5, 20.0); // 병렬 투영
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);	//GLUT 상태를 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);


	glutCreateWindow("투영방법예제");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}