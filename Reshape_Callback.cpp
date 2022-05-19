#include<stdlib.h>
#include<GL/glut.h>

void init(void) {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);		
}

void triangle(void) {
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(-0.5, -0.5);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(0.5, -0.5);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(-0.5, 0.5);
	glEnd();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	triangle();
	glFlush();
}


void reshape( int new_w, int new_h) {	// �������� w,h�� �ڵ����� ������ ��

	//������ ��ȭ���ѵ� �������ִ� �Լ�
	glViewport(0, 0, new_w, new_h);
	float WidthFactor = (float)new_w / 300;	//�츮�� ������ ������ ũ�Ⱑ 300��
	float HeightFactor = (float)new_h / 300;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// �Ʒ� �������� ���ο� �ִ� �׸��� ��Ÿ���ڴ�.
	//Reshape : ������ â�� ��ȭ�� ����, ���� ������ ������ �� �ֵ��� ��������
	//gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	gluOrtho2D(-1.0*WidthFactor, 1.0*WidthFactor, -1.0*HeightFactor, 1.0*HeightFactor);
}

int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;

}

/*
 ������ �ߴ� ���� ����� ��׷��� = ������ �ٲ�
 -> ������ â�� ũ�⸦ �����ص� �״�� ���� �ϴ� ����

 �ǹ�: ������ �� ��Ʈ�� �߽�, ����� ����Ʈ�� �߽� ��ġ -> ��ü ũ��, ��Ⱦ�� ����
*/