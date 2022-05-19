#include<stdlib.h>
#include<GL/glut.h>

static GLfloat spin = 0.0;

void display() {
	int r, g, b;
	
	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;

	glClear(GL_COLOR_BUFFER_BIT);

	//현재 사용하고 있는 정보 삽입(to 행렬)
	glPushMatrix();

	// (0.0,0.0)을 중심으로 spin
	glRotatef(spin, 0.0, 0.0, 1.0);

	glColor3f((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);
	glRectf(-25.0, -25.0, 25.0, 25.0);

	// 현재 사용중인 정보 꺼내기(from 행렬)
	glPopMatrix();

	//Double Buffering 이므로
	glutSwapBuffers();
}


void spinDisplay(void) {

	spin += 0.01;
	if (spin > 360.0)		spin -= 360.0;
	glutPostRedisplay();
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(250, 250);
	glutCreateWindow("02_5 사각형 회전");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();

	return 0;

}


