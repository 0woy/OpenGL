#include<GL/glut.h>
#include<stdio.h>

void init() {


	/*
	Position: x, y, z, w
	w-0: Ư�� ���⸸ ���� ���⼺����(like �¾�)
	w-1: ��ġ, ������ �Բ� ������ ��ġ��(����� �Ÿ���)

	Ambient: ��ü�� ��� ���⿡ ���� ���� �������� ����
	Diffuse: Ư�� ���⿡ �������� ����(���� ��� ����, �߿�!)
	Specular: Ư�� �������� ���� �ݻ�, Diffuse�� ���� ������ ����.


	*/


	//Lighting
	GLfloat light_position[] = { 1.0,2.0,3.0,1.0 };
	GLfloat light_ambient[]= {0.0, 1.0, 1.0, 1.0}; // �ֺ� �ݻ籤 ���
	GLfloat light_diffuse[] = { 0.0,0.0,1.0,1.0 }; // Ȯ�� �ݻ��� �Ի籤 ����: �̰� �ٲٸ� ��ü�� ���� �ٲ�
	GLfloat light_specualr[] = { 1.0,1.0,1.0,1.0 };	// ��� �ݻ��� �Ի籤 ���
	 
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position); //���� ��ġ ����
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);	// ������ ambient ����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);	// ������ Diffuse ����
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specualr);	// ������ Specular ����

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidTeapot(0.5);
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w,
			1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	}
	else
		glOrtho(-1.5*(GLfloat)w / (GLfloat)h,
			1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lighting");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}