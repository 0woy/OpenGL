#include <GL/glut.h>
#include <stdlib.h>

void display(void) {
	// ������� ����
	glColor3f(1.0, 1.0, 1.0);

	//�簢���� ��ǥ �Է�
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 0.25, 0.0);
	glVertex3f(0.75, 0.25, 0.0);
	glVertex3f(0.75, 0.75, 0.0);
	glVertex3f(0.25, 0.75, 0.0);
	glEnd();

	// �̰� ������� ������ ���ۿ��� ������ �ְ� �׷����� ����.
	glFlush();	//�簢���� ȭ�鿡 �׸�
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);	//���� ���۸� ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//���� ����: left, right, bottom, top, near, far
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);	//GLUT ���¸� �ʱ�ȭ


	// ���÷��̸�� ���� ����: Single buffer & RGBA color ��� ����
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// â�� ũ��� ��ġ ����
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);

	// ������ ����
	glutCreateWindow("01 �簢�� �׸���");
	init();

	//�ʿ��� �ݹ� �Լ� ���: �ſ� �߿���, ��쵵 �˾Ƶα�
	// call back: ��� ��Ȳ�� �߻��ϸ� �ڵ� ȣ�� 
	glutDisplayFunc(display);

	// ���� �̺�Ʈ ó�� ����
	// - �̺�Ʈ�� �߻��ϸ� ��ġ�ϴ� �ݹ� �Լ��� ��ϵǾ� �ִ� ���
	//��ϵ� �Լ��� �ڵ����� ȣ��,, �� �ڿ� �� �־�� ��.
	glutMainLoop();	// �̺�Ʈ ó�� ���� ����

	return 0;

}

/*
2022.03.16.
1. glClear: ���۸� ����.
- glClear(GLbitfield mask): 4�� ����.
- OR �����ڷ� �� �� �̻��� ���۸� �Ѳ����� ���� �� ����.

2. glColor 3f: 3f = RGB(float, 0.0 ~ 1.0)
- f��� Suffix ������ ��밡��. (ppt ����)

3. glBegin(GLenum mode);, glEnd(void);
- ��, ��, �� ���� �׸��� ���� ���
- begin, end ���̿� ���� ������ ����.
ex) glBegin(GL_POLYGON);

*/