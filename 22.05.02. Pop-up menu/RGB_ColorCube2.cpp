#include<math.h>
#include<GL/glut.h>
#include<stdio.h>

GLint winWidth = 600, winHeight = 600;
GLfloat eyeX = 0.0, eyeY = 0.0, eyeZ = 2.0;
GLfloat theta = 270.0, phi = 180.0;
GLfloat upX = 0.0, upY = 1.0, upZ = 0.0;
GLfloat r = 2.0;


void draw_cube() {

	// 앞쪽 면
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);	//white
	glVertex3f(0.5, 0.5, 0.5);
	glColor3f(1.0, 0.0, 1.0);	//Magenta
	glVertex3f(-0.5, 0.5, 0.5);
	glColor3f(1.0, 0.0, 0.0);	//Red
	glVertex3f(-0.5, -0.5, 0.5);
	glColor3f(1.0, 1.0, 0.0);	//Yellow
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// 오른쪽
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);	//white
	glVertex3f(0.5, 0.5, 0.5);
	glColor3f(1.0, 1.0, 0.0);	//Yellow
	glVertex3f(0.5, -0.5, 0.5);
	glColor3f(0.0, 1.0, 0.0);	//Green
	glVertex3f(0.5, -0.5, -0.5);
	glColor3f(0.0, 1.0, 1.0);	//Cyan
	glVertex3f(0.5, 0.5, -0.5);
	glEnd();

	// 위쪽
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);	//Magenta
	glVertex3f(-0.5, 0.5, 0.5);
	glColor3f(1.0, 1.0, 1.0);	//white
	glVertex3f(0.5, 0.5, 0.5);
	glColor3f(0.0, 1.0, 1.0);	//Cyan
	glVertex3f(0.5, 0.5, -0.5);
	glColor3f(0.0, 0.0, 1.0);	//Blue
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();


	// 왼쪽
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);	//Magenta
	glVertex3f(-0.5, 0.5, 0.5);
	glColor3f(0.0, 0.0, 1.0);	//Blue
	glVertex3f(-0.5, 0.5, -0.5);
	glColor3f(0.0, 0.0, 0.0);	//Black
	glVertex3f(-0.5,- 0.5, -0.5);
	glColor3f(1.0, 0.0, 0.0);	//Red
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// 아래
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);	//Red
	glVertex3f(-0.5, -0.5, 0.5);
	glColor3f(0.0, 0.0, 0.0);	//Black
	glVertex3f(-0.5, -0.5, -0.5);
	glColor3f(0.0, 1.0, 0.0);	//Green
	glVertex3f(0.5,- 0.5, -0.5);
	glColor3f(1.0, 1.0, 0.0);	//Yellow
	glVertex3f(0.5,- 0.5, 0.5);
	glEnd();


	// 뒤
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);	//Blue
	glVertex3f(-0.5, 0.5, -0.5);
	glColor3f(0.0, 1.0, 1.0);	//Cyan
	glVertex3f(0.5, 0.5, -0.5);
	glColor3f(0.0, 1.0, 0.0);	//Green
	glVertex3f(0.5, -0.5, -0.5);
	glColor3f(0.0, 0.0, 0.0);	//Black
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();


}


void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,- 1,1,1.6,300);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, upX, upY, upZ);

	glPolygonMode(GL_FRONT, GL_FILL);
	draw_cube();

	glutSwapBuffers();
}


void reshape(GLint newW, GLint newH) {
	glViewport(0, 0, newW, newH);
	winWidth = newW;
	winHeight = newH;
}


void eyePosition() {
	GLfloat dt = 1.0;

	//Reduce theta slightly to obtain another point on the same longitude line on the sphere.
	GLfloat eyeXtmp = r * sin(theta *0.0174532 - dt) * sin(phi*0.0174532);
	GLfloat eyeYtmp = r * cos(theta *0.0174532 - dt);
	GLfloat eyeZtmp = r * sin(theta *0.0174532 - dt) * cos(phi*0.0174532);

	// 

	//Spherical to Cartesian convertion.
	eyeX = r * sin(theta *0.0174532 ) * sin(phi*0.0174532);
	eyeY = r * cos(theta *0.0174532 );
	eyeZ = r * sin(theta *0.0174532) * cos(phi*0.0174532);

	upX = eyeXtmp - eyeX;
	upY = eyeYtmp-eyeY;
	upZ = eyeZtmp-eyeZ;

	glutPostRedisplay();
}


// OpenGL/ GLUT C code 
void onMouseMove(int x, int y) {

	//Mouse point to angle conversion
	theta = (360.0 / (double)winHeight)*(double)y*3.0; // 3.0 rotations possible
	phi = (360.0 / (double)winWidth)*(double)x*3.0;

	//Restrict the angles within 0 ~ 360 deg (optional)
	if (theta > 360)
		theta = fmod((double)theta, 360.0);
	if(phi > 360)
		phi= fmod((double)phi, 360.0);

	eyePosition();

}

void SpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		r -= 0.1;
	if (key == GLUT_KEY_DOWN)
		r += 0.1;

	eyePosition();
}


/*
은면제거: 깊이 테스팅 적용, Z축 기준,
Depth Test : 관찰자로부터 멀리 있는 것을 먼저 그려야 
우리가 그리고자 하는 게 그려짐.

*/ 

int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(50, 50);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutCreateWindow("Camera & REB Color Cube");

	init();
	glutDisplayFunc(display);	
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(onMouseMove);
	glutSpecialFunc(SpecialKeys);
	glutMainLoop();

	return 0;
}

