#include<GL/glut.h>
#include<GL/GLU.h>
#include<GL/GL.h>
#include<time.h>


unsigned char PALETTE[16][3] = {
{255,255,255},
{0,255,255},
{255,0,255},
{0,0,255},
{192,192,192},
{128,128,128},
{0,128,128},
{128,0,128},
{0,0,128},
{255,255,0},
{0,255,0},
{128,128,0},
{0,128,0},
{255,0,0},
{128,0,0},
{0,0,0}
};

GLfloat Delta = 0.0;
GLint Index = 0;
GLfloat Red = 0.0;
GLfloat Green = 0.0;
GLfloat Blue = 0.0;

void MyDisplay() {
	Red = PALETTE[Index][0] / 255.0f;
	Green = PALETTE[Index][1] / 255.0f;
	Blue = PALETTE[Index][2] / 255.0f;
	glColor3f(Red, Green, Blue);


	glBegin(GL_LINES);
		glVertex3f(-1.0 + Delta,1.0,0.0);
		glVertex3f(-1.0 - Delta, 1.0, 0.0);
		glVertex3f(-1.0, -1.0+Delta, 0.0);
		glVertex3f(1.0, 1.0 - Delta, 0.0);
	glEnd();
	glutSwapBuffers();
}

void MyTimer(int Value) {
	if (Delta < 2.0f)
		Delta += 0.01;
	else {
		Delta = 0.0;
		if (++Index >= 15)
		{
			Index = 0;
			glClear(GL_COLOR_BUFFER_BIT);
		} 
	}
	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 1);
}


int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Timer Callback ����");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutTimerFunc(10, MyTimer, 1);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();

	return 0;

}