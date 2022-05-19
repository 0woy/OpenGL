/*
	22.03.31.(목)
	lines.c
	This program demonstrates geomatric 

*/

#include<GL/glut.h>
#include<stdlib.h>

#define drawOneLine(x1,y1,x2,y2) glBegin(GL_LINES); \
	glVertex2f((x1),(y1)); glVertex2f((x2),(y2)); glEnd();

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display() {

	int i;
	glClear(GL_COLOR_BUFFER_BIT);

	//select white for all lines
	glColor3f(1.0, 1.0, 1.0);
	
	/* in 1st row, 3lines, each with a diffrent stipple */
	glEnable(GL_LINE_STIPPLE);

	glLineStipple(1, 0x0101); // dotted
	drawOneLine(50.0, 125.0, 150.0, 125.0);

	glLineStipple(1, 0x00FF); // dashed
	drawOneLine(150.0, 125.0, 250.0, 125.0);

	glLineStipple(1, 0x1C47); // dash/dot/dash
	drawOneLine(250.0, 125.0, 350.0, 125.0);

	/* in 2nd row, 3 wide lines, each with different stipple
	 ex) pattern				factor 
		0011 : xxoo				bit 하나당 대응되는 점 개수
		0110 : xoox		
	*/
	glLineWidth(5.0);
	glLineStipple(1, 0x0101); // dash/dot/dash
	drawOneLine(50.0, 100.0, 150.0, 100.0);
	glLineStipple(1, 0x00FF); // dash/dot/dash
	drawOneLine(150.0, 100.0, 250.0, 100.0);
	glLineStipple(1, 0x1C47); // dash/dot/dash
	drawOneLine(250.0, 100.0, 350.0, 100.0);


	/* in 3rd row, 6 lines, with dash/dot/dash stipple */
	/* as part of a single connected line strip */
	glLineStipple(1, 0x1C47);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < 7; i++) {
		glVertex2f(50.0 + ((GLfloat)i *50.0), 75.0);
	 }
	glEnd();

	/* in 4th row, 6 independent lines with sample stipple */
	for (i = 0; i < 6; i++) {
		drawOneLine(50.0 + ((GLfloat)i*50.0), 50.0, 50.0 + ((GLfloat)(i + 1)*50.0), 50.0);
	}

	/* in 5th row, 1 line, with dash/dot/dash stipple */
	/* and a stipple repeat factor of 5 */
	glLineStipple(5, 0x1C47);
	drawOneLine(50.0, 25.0, 350.0, 25.0);

	glDisable(GL_LINE_STIPPLE);
	glFlush();

}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27: exit(0);

	}
}


int main(int argc, char ** argv ) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 150);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}