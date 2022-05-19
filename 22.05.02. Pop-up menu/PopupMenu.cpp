
#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>

void display() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glColor3f(0, 0, 0);
	glFlush();
}


// 메뉴를 선택했을 떄 수행되는 함수
void main_menu_select(int v) {
	switch (v) {
	case 1:
		glutSetWindowTitle("First mode ..");
		printf("첫번째 메뉴를 선택하셨습니다.\n");
		break;

	case 2:
		glutSetWindowTitle("Second mode ..");
		printf("두번째 메뉴를 선택하셨습니다.\n");
		break;

	case 3:
		glutSetWindowTitle("Third mode ..");
		printf("세번째 메뉴를 선택하셨습니다.\n");
		break;

	case 666:
		printf("프로그램 종료..\n");
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

	// Pop-up 메뉴를 생성하고 세부메뉴의 이름과 메뉴의 번호를 할당
	glutCreateMenu(main_menu_select);
	glutAddMenuEntry("First", 1);
	glutAddMenuEntry("Second", 2);
	glutAddMenuEntry("Third", 3);
	glutAddMenuEntry("Quit", 666);

	// 마우스 오른쪽 버튼을 누르면 메뉴 생성
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}



















