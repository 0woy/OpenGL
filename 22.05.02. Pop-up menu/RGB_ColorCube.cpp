#include<GL/glut.h>
#include<GL/GL.h>
#include<GL/GLU.h>


GLfloat Verrtices[8][3] = {
	{-0.25,-0.25,0.25},
	{-0.25,0.25,0.25},
	{0.25,0.25,0.25},
	{0.25,-0.25,0.25},
	{-0.25,-0.25,-0.25},
	{-0.25,0.25,-0.25},
	{0.25,0.25,-0.25},
	{0.25,-0.25,-0.25}
};

GLfloat Colors[8][3] = {
	{0.2,0.2,0.2},
	{1.0,0,0},
	{1,1,0},
	{0, 1, 0},
	{0, 0, 1},
	{1,0,1},
	{1, 1, 1},
	{0,1,1}
};

// 시계방향을 통해 위쪽 면을 보도록 해야함.
// 즉, 순서에 유의하면서 해야함.
// 표면은 보통 반시계방향으로 정의된 면임.
GLubyte VertexList[24] = {
	0,3,2,1,		
	2,3,7,6,
	0,4,7,3,
	1,2,6,5,
	4,5,6,7,
	0,1,5,4
};


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, Colors);
	glVertexPointer(3, GL_FLOAT, 0, Verrtices);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(30.0, 1.0, 1.0, 1.0);
	for (int i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &VertexList[4 * i]);
		
	}
	glFlush();

}



int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode( GLUT_RGB);
	glutCreateWindow("OpenGL Verttex Array Example");
	glutDisplayFunc(display);
	glMatrixMode(GL_PROJECTION);

	glClearColor(1, 1, 1, 1);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}


