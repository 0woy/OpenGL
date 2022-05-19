#include<stdlib.h>
#include<time.h>
#include<GL/glut.h>

static int delay = 500;

void init() {
	srand(time(0));
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void display() {
	int x1, y1, x2, y2, r, g, b;

	x1 = rand() % 51;
	y1 = rand() % 51;
	x2 = rand() % 51;
	y2 = rand() % 51;
	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;

	glColor3f((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);

	// 정점의 순서가 중요함. 한 방향으로 그려져야 함.
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	//glVertex2f(x2, y1);
	glEnd();

	glFlush();
}

void timer(int t) {

	// display 함수 호출, 필요한 이유를 알아야함.
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}

int main(int argc, char* argv[]) {
	
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Prog02: Random boxes");
	glutDisplayFunc(display);

	/* call back 함수, delay 값(10ms) 지난 후 timer 호출
	 - 반복해서 호출해야하므로 timer 함수에서 재귀
	 timer 함수 => display 호출
	 */
	glutTimerFunc(delay, timer,0);

	init();
	glutMainLoop();



	return 0;
}