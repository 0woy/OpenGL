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
	glTranslatef(-1.5, 0.0, 1.5); //��ü �̵��� ���� ��ȭ Ȯ��
	glutWireCube(1.0);

	glPopMatrix();

	glColor3f(0.0, 0.0, 1.0);	//blue
	glTranslatef(1.5, 0.0, 1.5);	//��ü�� �̵��� ���� ��ȭ Ȯ��
	glutWireCube(1.0);

	glFlush();

}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);	//���� ����
	//glOrtho(-7.0, 7.0, -7.0, 7.0, 1.5, 20.0); // ���� ����
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);	//GLUT ���¸� �ʱ�ȭ
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);


	glutCreateWindow("�����������");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}