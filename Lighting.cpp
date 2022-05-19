#include<GL/glut.h>
#include<stdio.h>

void init() {


	/*
	Position: x, y, z, w
	w-0: 특정 방향만 가진 방향성광원(like 태양)
	w-1: 위치, 방향을 함께 가지는 위치광(가까운 거리만)

	Ambient: 물체의 모든 방향에 대해 고르게 비춰지는 조명
	Diffuse: 특정 방향에 비춰지는 조명(면의 명암 결정, 중요!)
	Specular: 특정 방향으로 조명 반사, Diffuse와 같은 값으로 설정.


	*/


	//Lighting
	GLfloat light_position[] = { 1.0,2.0,3.0,1.0 };
	GLfloat light_ambient[]= {0.0, 1.0, 1.0, 1.0}; // 주변 반사광 녹색
	GLfloat light_diffuse[] = { 0.0,0.0,1.0,1.0 }; // 확산 반사의 입사광 적색: 이걸 바꾸면 물체의 색이 바뀜
	GLfloat light_specualr[] = { 1.0,1.0,1.0,1.0 };	// 경면 반사의 입사광 백색
	 
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position); //조명 위치 설정
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);	// 조명의 ambient 설정
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);	// 조명의 Diffuse 설정
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specualr);	// 조명의 Specular 설정

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidTeapot(0.5);
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w,
			1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	}
	else
		glOrtho(-1.5*(GLfloat)w / (GLfloat)h,
			1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lighting");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}