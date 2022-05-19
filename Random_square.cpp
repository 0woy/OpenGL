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

	// ������ ������ �߿���. �� �������� �׷����� ��.
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	//glVertex2f(x2, y1);
	glEnd();

	glFlush();
}

void timer(int t) {

	// display �Լ� ȣ��, �ʿ��� ������ �˾ƾ���.
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}

int main(int argc, char* argv[]) {
	
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Prog02: Random boxes");
	glutDisplayFunc(display);

	/* call back �Լ�, delay ��(10ms) ���� �� timer ȣ��
	 - �ݺ��ؼ� ȣ���ؾ��ϹǷ� timer �Լ����� ���
	 timer �Լ� => display ȣ��
	 */
	glutTimerFunc(delay, timer,0);

	init();
	glutMainLoop();



	return 0;
}