#include<GL/glut.h>
#include<stdlib.h>
#include<GL/GLU.h>
#include<stdio.h>
#include<GL/GL.h>
#include<time.h>

#define maximum 100	// 찍을 수 있는 별 100개

float star_p[maximum][2] = { 250,250 };	// 별(마우스) 위치 저장, 초기화면 별 (250,250)

int count = 1;				// 전체 별 개수
int currentWidth = 500;		// Window_Width
int currentHeight = 500;	// Window_Height
bool L_flag = false;		// 마우스 왼쪽버튼 감지
bool R_flag = false;		
int dir = 1;			// 별의 회전 방향 결정(t:right, F:left);

// 초기 별 색깔: 하얀색
float r = 1.0;
float g = 1.0;
float b = 1.0;

static GLfloat spin = 0.0;

void init() {

	glClearColor(0.0, 0.0, 0.0,0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION); 
	glOrtho(0.0,500.0, 500.0, 0.0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glShadeModel(GL_FLAT);
}

 
// 별 찍기
void draw_stars(int i) {
	glBegin(GL_TRIANGLES);
	glVertex3f(star_p[i][0] - 50, star_p[i][1] - 25, 0);
	glVertex3f(star_p[i][0], star_p[i][1] + 50, 0);
	glVertex3f(star_p[i][0] + 50, star_p[i][1] - 25, 0);
	glVertex3f(star_p[i][0] - 50, star_p[i][1] + 25, 0);
	glVertex3f(star_p[i][0] + 50, star_p[i][1] + 25, 0);
	glVertex3f(star_p[i][0], star_p[i][1] - 50, 0);
	glEnd();
}

// 중점을 잇는 선분
void draw_lines(int i) {
	glBegin(GL_LINES);
	glVertex3f(star_p[i][0], star_p[i][1], 0);
	glVertex3f(star_p[i + 1][0], star_p[i + 1][1], 0);
	glEnd();
}

void spin_star(int i) {
	

		glPushMatrix();
		glTranslatef(star_p[i][0], star_p[i][1], 0);

		switch (dir) {
		case 0:
			glRotatef(spin, 0.0, 0.0, 1.0);
			break;
		case 1:
			glRotatef(- spin, 0.0, 0.0, 1.0);
			break;
		}
		glTranslatef(-star_p[i][0], -star_p[i][1], 0);
		draw_stars(i);


	glLoadIdentity();

	// 현재 사용중인 정보 꺼내기(from 행렬)
	
	
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(r,g,b);
	//glEnableClientState(GL_VERTEX_ARRAY); //배열 사용 가능


	// Click R_Btn
	if (R_flag) {
		L_flag = false;		// 기존에 있던 멈춰있는 별 삭제

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		for (int i = 0; i < count; i++) {
			if (i == count - 1)
				spin_star(i);
			else {
				draw_lines(i);
				spin_star(i);
			}
			
		}

		glPopMatrix();
	}

	 // Click L_Btn
	if (L_flag) {

		for (int i = 0; i < count; i++) {
			if (i == count - 1)
				draw_stars(i);

			else {
				draw_stars(i);
				draw_lines(i);
			}
		}
	} 
		
	// 초기 화면
	if(!R_flag)
		draw_stars(0);

	glutSwapBuffers();

}

void reshape(int w, int h) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	

	float WidthFactor = (float)w / 500;
	float HeightFactor = (float)h / 500;

	gluOrtho2D(0.0, 500*WidthFactor, 500*HeightFactor, 0.0);


	glutPostRedisplay();
}

void spinDisplay(void) {

	spin += 0.015;
	if (spin > 360.0)
		spin -= 360.0;
	else if (spin < -360)
		spin += 360;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'q':
		exit(0);
		break;
	}
}

void mouseProcess(int button, int state, int mousex, int mousey) {

		// 별 추가
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		L_flag = true;
		star_p[count][0] = mousex;
		star_p[count][1] = mousey;
		count++;
		glutPostRedisplay();
		}
	
		// 회전 시키기
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			R_flag = true;
			spin = 0.0;
			glutIdleFunc(spinDisplay);
			dir = (dir + 1) % 2;
			
	}

		//색깔 바꾸기
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		r = (float)(rand() % 256) / 255;
		g = (float)(rand() % 256) / 255;
		b = (float)(rand() % 256) / 255;
		glutPostRedisplay();
	}


}


int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(currentWidth, currentHeight);
	glutCreateWindow("Stars");
	 
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseProcess);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}