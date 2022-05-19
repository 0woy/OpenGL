/*
한 면을 뚫려있음
은면: 활성화를 해야 보이지 않는 면을 없애줘서 원하는 대로 잘 보임.
컬링: 활성화시 뒷면이 보이지 않음.
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
	glutAddMenuEntry("은면제거 on", 1);
	glutAddMenuEntry("은면제거 off", 2);
	menu_cull_test = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("컬링 on", 3);
	glutAddMenuEntry("컬링 off", 4);

	menu_main = glutCreateMenu(MenuFunc);
	glutAddSubMenu("은면제거", menu_depth_test);
	glutAddSubMenu("컬링", menu_cull_test);
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


		// inner of back : 정점 방향 유의
		// 컬링 on 시에 보이게 됨. 
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

	// 원근 투영
	GLfloat fAspect;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	fAspect = (float)w / (float)h;
	gluPerspective(60.0, fAspect, 1, 500);
	glTranslatef(0, 0, -300);
	glRotatef(30.0, 1.0, 0, 0);
	//glRotatef(45.0, 0, 1, 0);

	// 모델 뷰 행렬스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutSwapBuffers();

}

void TimerFunc(int v) {
	yRot += 1.0f;

	glutPostRedisplay();	// 화면 재 출력
	glutTimerFunc(TIMER, TimerFunc, 1);	// 타이머함수 재설정
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