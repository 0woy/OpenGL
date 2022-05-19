#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include <algorithm>

using namespace std;

#define MAX 100

int Win_W = 500, Win_H = 500;	// 화면 사이즈
int mousex, mousey;	// 마우스 위치
bool First = true; // 초기의 점
bool Poly = false;	// 오른쪽 버튼 감지
bool drag = false;
bool select = false;

int num = 0; // 라인 개수

float r = 0, g = 0, b = 0;
bool control = false;
int CurrentX, CurrentY; // motion에 사용될 현재 위치



bool R_flag = false;	// 회전
int dir = 1;	// 회전 방향
static GLfloat spin = 0.0;	// 회전 각도


// Rubber-Band를 만들기 위해 위치를 저장할 공간
struct{
	int x1, y1, x2, y2;
}Points[MAX];


// 드래그 공간을 저장할 x,y
struct {
	int x, y;
}Drags[2];

int X_MAX, Y_MAX, X_MIN, Y_MIN;

int sort_arr[MAX][2] = {0};




void init() {
	glClearColor(1.0, 1.0, 0.0, 0.0);
}

// 드래그 범위를 정하기 위한 X,Y 최대 최소 찾기.
void sort() {
	int i = 0;
	for (i = 0; i <= num; i++) {
		sort_arr[i][0] = Points[i].x1;
		sort_arr[i][1] = Points[i].y1;
	}
		
	X_MAX = sort_arr[0][0];
	Y_MAX = sort_arr[0][1];
	X_MIN = sort_arr[0][0];
	Y_MIN = sort_arr[0][1];

	//sort(sort_arr, sort_arr + MAX);

	for (int i = 0; i <= num; i++) {
		if (X_MAX < sort_arr[i][0])
			X_MAX = sort_arr[i][0];

		if (X_MIN > sort_arr[i][0])
			X_MIN = sort_arr[i][0];

		if (Y_MAX < sort_arr[i][1])
			Y_MAX = sort_arr[i][1];

		if (Y_MIN > sort_arr[i][1])
			Y_MIN = sort_arr[i][1];
	}
}


// Line 그리기
void draw_line(int n) {
	glBegin(GL_LINES);
	glVertex2i(Points[n].x1, Points[n].y1);
	glVertex2i(Points[n].x2, Points[n].y2);
	glEnd();
}

// 누른 위치 점찍기
void draw_point(int n) {
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2i(Points[n].x1, Points[n].y1);
	glVertex2i(Points[n].x2, Points[n].y2);
	glEnd();
}

// 버튼을 뗀 채로 mouse 움직임 감지
void PassiveMouse(int x, int y) {
	mousex = x;
	mousey = y;
	glutPostRedisplay();
}


void draw_square() {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(Drags[0].x, Drags[0].y);
	glVertex2i(Drags[0].x, CurrentY);
	glVertex2i(CurrentX, CurrentY);
	glVertex2i(CurrentX, Drags[0].y);
	glVertex2i(Drags[0].x, Drags[0].y);
	glEnd();
}


// 회전하기 위한 함수
void spin_points(int i) {

	glPushMatrix();
	glTranslatef(Points[i].x1, Points[i].y1, 0);
	glTranslatef(Points[i].x2, Points[i].y2, 0);

	switch (dir) {
	case 0:
		glRotatef(spin, 0.0, 0.0, 1.0);
		break;
	case 1:
		glRotatef(-spin, 0.0, 0.0, 1.0);
		break;
	}
	glTranslatef(-Points[i].x1, -Points[i].y1, 0);
	glTranslatef(-Points[i].x2, -Points[i].y2, 0);
	
	glBegin(GL_POLYGON);
	for (i = 0; i < num; i++) {
		glVertex2i(Points[i].x1, Points[i].y1);
		glVertex2i(Points[i].x2, Points[i].y2);
	}
	glEnd();


	glLoadIdentity();
	// 현재 사용중인 정보 꺼내기(from 행렬)
}

/*
void spinDisplay(void) {

	spin += 0.015;
	if (spin > 360.0)
		spin -= 360.0;
	else if (spin < -360)
		spin += 360;

	glutPostRedisplay();
}
*/


void display() {
	sort();
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);

	for (i = 0; i < num; i++) {
		draw_point(i);
		draw_line(i);
	}
	
	if (!First && !Poly) // 처음 점이 아니라면
	{
		if (num < MAX - 1) {
			glBegin(GL_LINES);
			glVertex2i(Points[i].x1, Points[i].y1);
			glVertex2i(mousex, mousey);
			glEnd();
		}
	}

	// 오른쪽 버튼이 눌리면 마지막 점과 처음 점 잇기, 폴리곤 채우기.
	if (Poly) {
		glColor3f(r, g, b);

		// 점 하나만 찍고 우클릭을 눌렀을 때, 점만 나오게 함.
		if (num < 1) {
			glPointSize(5);
			glBegin(GL_POINTS);
			glVertex2i(Points[0].x1, Points[0].y1);

			/*
			다시 초기화 시키는 코드
			First = true;
			Poly = false;
			*/
		}
		else {
			for (int i = 0; i < num; i++) {
				draw_point(i);
				draw_line(i);
			}

			glBegin(GL_LINES);
			glVertex2i(Points[0].x1, Points[0].y1);
			glVertex2i(Points[num - 1].x2, Points[num - 1].y2);
			glEnd();


			glBegin(GL_POLYGON);
			for (i = 0; i < num; i++) {
				glVertex2i(Points[i].x1, Points[i].y1);
				glVertex2i(Points[i].x2, Points[i].y2);
			}
			glEnd();
		}


	}
	if (drag) {
		//sort();
		if (select) {
			draw_square();
		}
	}

	glutSwapBuffers();
	
}


void motion(int mouseX, int mouseY) {
	CurrentX= mouseX;
	CurrentY = mouseY;
	glutPostRedisplay();
}


void mouse(int button, int state, int x, int y) {

	// 왼쪽 버튼 = Rubber-Band 그리기 || 드래그 하기
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (First) {
			First = false;
			Points[num].x1= x;
			Points[num].y1 = y;
		}

		// 오른쪽 버튼 누르기 전
		else if(!Poly){
			if (num < MAX - 1) {
				Points[num].x2 = x;
				Points[num].y2 = y;
				num++;
			}
			// STRIP를 위해 위치 바꿔주기
			Points[num].x1 = Points[num-1].x2;
			Points[num].y1 = Points[num-1].y2;
		}

		else if (drag&&!R_flag) {
			select = true;
		//	printf("TX =%d , TY =%d\n", x, y);
			Drags[0].x = x;
			Drags[0].y = y;
		}
	}

	// 왼쪽 떼기
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && drag) {
		sort();
		//printf("BX =%d , BY =%d\n", x, y);
		//printf("xMAX =%d, yMAX =%d, xMin =%d, yMIN =%d \n", X_MAX, Y_MAX, X_MIN, Y_MIN);
		// 폴리곤 전체 선택시 드래그 활성화
		if (Drags[0].x <= X_MIN && Drags[0].y >= Y_MAX && x >= X_MAX && y <= Y_MIN) {
		
			select = false;
			Drags[1].x = x;
			Drags[1].y = y;
			drag = false;
		}
		//Drags[0].x = x;
		//Drags[0].y = y;
		R_flag = true; // 회전 활성화
		glutPostRedisplay();
		
	}

	// 오른쪽 버튼 = 단색으로 채운 폴리곤,Rubber-Band 비활성화
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {	
		Poly = true;
		drag = true;
		r = (float)(rand() % 256) / 255;
		g = (float)(rand() % 256) / 255;
		b = (float)(rand() % 256) / 255;
		glutPostRedisplay();

		
	}

	// 가운데 버튼 = 초기화
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		num= 0;
		Poly = false; // 우클릭시 폴리곤 비활성화 
		First = true; // 처음 점 활성화(초기 화면)
		drag = false; // drag 비활성화
		select = false; 
		R_flag = false; // 회전 비활성화
		//glPopMatrix();
		glutPostRedisplay();
	}
}

void reshape(int w, int h) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);


	float WidthFactor = (float)w / Win_W;
	float HeightFactor = (float)h / Win_H;

	gluOrtho2D(0.0, Win_W* WidthFactor, Win_H * HeightFactor, 0.0);

	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(Win_W, Win_H);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Middle Exam");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(PassiveMouse);
	glutMotionFunc(motion);

	glutMainLoop();
	return 0;
}