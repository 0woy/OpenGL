
#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>

void display() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glColor3f(0, 0, 0);
	glFlush();
}


// �޴��� �������� �� ����Ǵ� �Լ�
void main_menu_select(int v) {
	switch (v) {
	case 1:
		glutSetWindowTitle("First mode ..");
		printf("ù��° �޴��� �����ϼ̽��ϴ�.\n");
		break;

	case 2:
		glutSetWindowTitle("Second mode ..");
		printf("�ι�° �޴��� �����ϼ̽��ϴ�.\n");
		break;

	case 3:
		glutSetWindowTitle("Third mode ..");
		printf("����° �޴��� �����ϼ̽��ϴ�.\n");
		break;

	case 666:
		printf("���α׷� ����..\n");
		exit(0);
		break;
	}
}


int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("menu example");
	glutDisplayFunc(display);

	// Pop-up �޴��� �����ϰ� ���θ޴��� �̸��� �޴��� ��ȣ�� �Ҵ�
	glutCreateMenu(main_menu_select);
	glutAddMenuEntry("First", 1);
	glutAddMenuEntry("Second", 2);
	glutAddMenuEntry("Third", 3);
	glutAddMenuEntry("Quit", 666);

	// ���콺 ������ ��ư�� ������ �޴� ����
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}



















