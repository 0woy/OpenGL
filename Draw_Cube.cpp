//22.04.04.
//��������: ���ٹ� ����X
//CLIP: viewing �ڽ� �ȿ� �ִ� ��ü�� �׸��� ��, �ٱ��� ������ �߸�

#include<GL/glut.h>
#include<stdlib.h>

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();

	/* Viewing Transformation */
	// upx,y,z : ī�޶��� ����, ����, Z
	gluLookAt(5.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	/* Modeling Transformation */
	glScalef(1.0, 2.0, 1.0);
	glutWireCube(1.0);
	//��ü�� Ŀ���� �ϴ� ���: ũ�⸦ Ű���, ī�޶��� ��ġ�� �������Ѵ�(in Perspective view)

	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	//glViewport(100,200,400, 300);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //��� �ʱ�ȭ
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Transformed Cube");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}



