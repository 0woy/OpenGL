#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include <algorithm>

using namespace std;

#define MAX 100

int Win_W = 500, Win_H = 500;	// ȭ�� ������
int mousex, mousey;	// ���콺 ��ġ
bool First = true; // �ʱ��� ��
bool Poly = false;	// ������ ��ư ����
bool drag = false;
bool select = false;

int num = 0; // ���� ����

float r = 0, g = 0, b = 0;
bool control = false;
int CurrentX, CurrentY; // motion�� ���� ���� ��ġ



bool R_flag = false;	// ȸ��
int dir = 1;	// ȸ�� ����
static GLfloat spin = 0.0;	// ȸ�� ����


// Rubber-Band�� ����� ���� ��ġ�� ������ ����
struct{
	int x1, y1, x2, y2;
}Points[MAX];


// �巡�� ������ ������ x,y
struct {
	int x, y;
}Drags[2];

int X_MAX, Y_MAX, X_MIN, Y_MIN;

int sort_arr[MAX][2] = {0};




void init() {
	glClearColor(1.0, 1.0, 0.0, 0.0);
}

// �巡�� ������ ���ϱ� ���� X,Y �ִ� �ּ� ã��.
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


// Line �׸���
void draw_line(int n) {
	glBegin(GL_LINES);
	glVertex2i(Points[n].x1, Points[n].y1);
	glVertex2i(Points[n].x2, Points[n].y2);
	glEnd();
}

// ���� ��ġ �����
void draw_point(int n) {
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2i(Points[n].x1, Points[n].y1);
	glVertex2i(Points[n].x2, Points[n].y2);
	glEnd();
}

// ��ư�� �� ä�� mouse ������ ����
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


// ȸ���ϱ� ���� �Լ�
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
	// ���� ������� ���� ������(from ���)
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
	
	if (!First && !Poly) // ó�� ���� �ƴ϶��
	{
		if (num < MAX - 1) {
			glBegin(GL_LINES);
			glVertex2i(Points[i].x1, Points[i].y1);
			glVertex2i(mousex, mousey);
			glEnd();
		}
	}

	// ������ ��ư�� ������ ������ ���� ó�� �� �ձ�, ������ ä���.
	if (Poly) {
		glColor3f(r, g, b);

		// �� �ϳ��� ��� ��Ŭ���� ������ ��, ���� ������ ��.
		if (num < 1) {
			glPointSize(5);
			glBegin(GL_POINTS);
			glVertex2i(Points[0].x1, Points[0].y1);

			/*
			�ٽ� �ʱ�ȭ ��Ű�� �ڵ�
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

	// ���� ��ư = Rubber-Band �׸��� || �巡�� �ϱ�
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (First) {
			First = false;
			Points[num].x1= x;
			Points[num].y1 = y;
		}

		// ������ ��ư ������ ��
		else if(!Poly){
			if (num < MAX - 1) {
				Points[num].x2 = x;
				Points[num].y2 = y;
				num++;
			}
			// STRIP�� ���� ��ġ �ٲ��ֱ�
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

	// ���� ����
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && drag) {
		sort();
		//printf("BX =%d , BY =%d\n", x, y);
		//printf("xMAX =%d, yMAX =%d, xMin =%d, yMIN =%d \n", X_MAX, Y_MAX, X_MIN, Y_MIN);
		// ������ ��ü ���ý� �巡�� Ȱ��ȭ
		if (Drags[0].x <= X_MIN && Drags[0].y >= Y_MAX && x >= X_MAX && y <= Y_MIN) {
		
			select = false;
			Drags[1].x = x;
			Drags[1].y = y;
			drag = false;
		}
		//Drags[0].x = x;
		//Drags[0].y = y;
		R_flag = true; // ȸ�� Ȱ��ȭ
		glutPostRedisplay();
		
	}

	// ������ ��ư = �ܻ����� ä�� ������,Rubber-Band ��Ȱ��ȭ
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {	
		Poly = true;
		drag = true;
		r = (float)(rand() % 256) / 255;
		g = (float)(rand() % 256) / 255;
		b = (float)(rand() % 256) / 255;
		glutPostRedisplay();

		
	}

	// ��� ��ư = �ʱ�ȭ
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		num= 0;
		Poly = false; // ��Ŭ���� ������ ��Ȱ��ȭ 
		First = true; // ó�� �� Ȱ��ȭ(�ʱ� ȭ��)
		drag = false; // drag ��Ȱ��ȭ
		select = false; 
		R_flag = false; // ȸ�� ��Ȱ��ȭ
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