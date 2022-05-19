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


void reshape( int new_w, int new_h) {	// 윈도우의 w,h를 자동으로 가지고 옴

	//비율을 변화시켜도 유지해주는 함수
	glViewport(0, 0, new_w, new_h);
	float WidthFactor = (float)new_w / 300;	//우리가 설정한 윈도우 크기가 300임
	float HeightFactor = (float)new_h / 300;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 아래 투영공간 내부에 있는 그림만 나타내겠다.
	//Reshape : 윈도우 창의 변화를 감지, 같은 비율을 유지할 수 있도록 연산해줌
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
 이전에 했던 것은 모양이 찌그러짐 = 비율이 바뀜
 -> 윈도우 창의 크기를 조절해도 그대로 유지 하는 예제

 의미: 기존의 뷰 포트의 중심, 변경된 뷰포트의 중심 일치 -> 물체 크기, 종횡비 유지
*/