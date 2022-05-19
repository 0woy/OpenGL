/*
�� ���� �շ�����
����: Ȱ��ȭ�� �ؾ� ������ �ʴ� ���� �����༭ ���ϴ� ��� �� ����.
�ø�: Ȱ��ȭ�� �޸��� ������ ����.
*/


#include<stdlib.h>
#include<time.h>
#include<GL/glut.h>

#define W 800
#define H 600
#define AXIS_SIZE  60
#define TIMER 100

void SetupRC();
void RenderScene();
void ChangeSize(int w, int h);
void TimerFunc(int v);
void MenuFunc(int button);

float yRot = 0.0f;
int menu_main;
int menu_depth_test;
int menu_cull_test;

int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(W,H);
	glutCreateWindow("Hidden Surface");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutTimerFunc(TIMER, TimerFunc, 1);

	//Popup menu
	menu_depth_test = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("�������� on", 1);
	glutAddMenuEntry("�������� off", 2);
	menu_cull_test = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("�ø� on", 3);
	glutAddMenuEntry("�ø� off", 4);

	menu_main = glutCreateMenu(MenuFunc);
	glutAddSubMenu("��������", menu_depth_test);
	glutAddSubMenu("�ø�", menu_cull_test);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	SetupRC();
	glutMainLoop();

	return 0;

}

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glLoadIdentity();
	glRotatef(yRot, 0, 1, 0);

	glBegin(GL_QUADS);
	{
		// front
		glColor3f(1, 0, 0); //red
		glVertex3f(50, 50, 50);
		glVertex3f(-50, 50, 50);
		glVertex3f(-50, -50, 50);
		glVertex3f(50, -50, 50);

		
		//left
		glColor3f(0, 1, 0); //green
		glVertex3f(-50, 50, 50);
		glVertex3f(-50, 50, -50);
		glVertex3f(-50, -50, -50);
		glVertex3f(-50, -50, 50);


		// back
		glColor3f(0, 0, 1); //blue
		glVertex3f(-50, 50, -50);
		glVertex3f(50, 50, -50);
		glVertex3f(50, -50, -50);
		glVertex3f(-50, -50, -50);


		// inner of back : ���� ���� ����
		// �ø� on �ÿ� ���̰� ��. 
		glColor3f(0, 0, 1); //blue
		glVertex3f(-50, 50, -50);
		glVertex3f(-50, -50, -50);
		glVertex3f(50, -50, -50);
		glVertex3f(50, 50, -50);
	}
	glEnd();
	glPopMatrix();

	glutSwapBuffers();

}


void SetupRC() {
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glClearColor(0, 0, 0, 1);
}

void ChangeSize(int w, int h) {
	GLfloat nRange = 100.0f;
	glViewport(0, 0, w, h);

	// ���� ����
	GLfloat fAspect;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	fAspect = (float)w / (float)h;
	gluPerspective(60.0, fAspect, 1, 500);
	glTranslatef(0, 0, -300);
	glRotatef(30.0, 1.0, 0, 0);
	//glRotatef(45.0, 0, 1, 0);

	// �� �� ��Ľ��� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutSwapBuffers();

}

void TimerFunc(int v) {
	yRot += 1.0f;

	glutPostRedisplay();	// ȭ�� �� ���
	glutTimerFunc(TIMER, TimerFunc, 1);	// Ÿ�̸��Լ� �缳��
}


void MenuFunc(int button) {

	switch (button)
	{
	case 1:
		glEnable(GL_DEPTH_TEST);
		break;
	case 2:
		glDisable(GL_DEPTH_TEST);
		break;
	case 3:
		glEnable(GL_CULL_FACE);
		break;
	case 4:
		glDisable(GL_CULL_FACE);
		break;
	}
	glutPostRedisplay();
}