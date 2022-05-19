#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>

/*
 Description: user-specific initialization (the window using black color)
 Input: None
 Output: The clear color is setted with black
*/

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
}


/*
 Description: The displat callback is invoked in response to window event
 Input: None
 Output: The clear Color is setted with black and display
*/
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glFlush();
}


/* 
 Description: 
 Input:
 Output:
*/

void mouseProcess(int button, int state, int x, int y) {

	//왼쪽 버튼 클릭
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		printf("Left mouse button is pressed.. \a,\n");
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		printf("Middle mouse button is pressed.. \a,\n");
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		printf("Right mouse button is pressed.. \a,\n");
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		printf("Left mouse button is released.. \a,\n");
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		printf("Middle mouse button is released.. \a,\n");
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		printf("Right mouse button is released.. \a,\n");
	}
}

void mousePassiveMotion(int x, int y) {
	printf("Current mouse position %d ,%d\n", x, y);
}

void mouseActiveMotion(int x, int y) {
	printf("Pressed mouse positon: %d %d\n", x, y);
}

void mouseEntry(int state) {
	if (state == GLUT_LEFT) {
		printf("Mouse is outside of window..\a\n");
	}
	else if (state == GLUT_ENTERED) {
		printf("Mouse is inside of window..\a\n");
	}
}

void keyboard(unsigned char key, int x, int y) {
	
	switch (key) {
	case 'a':
		printf("a is pressed.. %d, %d\a\n", x, y);
		break;
	case 'b':
		printf("b is pressed.. %d, %d\a\n", x, y);
		break;
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Mouse and Keyboard");

	init();
	glutDisplayFunc(display);
	// glutKeyboardFunc(keyboard);	//keyboard 눌린 부분 출력
	// glutMouseFunc(mouseProcess);	// mouse 버튼 출력
	
	glutPassiveMotionFunc(mousePassiveMotion); // 마우스 현재 위치 출력
	glutMotionFunc(mouseActiveMotion);	// 누른 상태로 움직인 위치 출력
	//glutEntryFunc(mouseEntry);	// Window 밖/안 출력

	glutMainLoop();
	return 0;
}