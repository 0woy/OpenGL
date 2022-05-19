// 왼쪽 마우스를 누르고 있을 시 Rubber band

#include <iostream>
#include <GL/glut.h>
#define MAXPOINTS 100
GLint points[MAXPOINTS][2];
int point_num = 0;

bool rubberband = true;

void init() {

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, 500.0, 500.0, 0.0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glShadeModel(GL_FLAT);
}


void draw_line(int k) {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	glVertex2iv(points[k]);
	glVertex2iv(points[k-1]);
	glEnd();
	glFlush();
}



void draw_points(int k) {

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2iv(points[k]);
	glEnd();
	glFlush();

}

void rubber() {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < point_num; ++i)
	{
		glVertex2iv(points[i]);
	}
	glEnd();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	/// Draw all the lines

		/// Stroke Color (White)
		glColor3f(1.0, 1.0, 1.0);
		for (int i = 1; i < point_num; i++)
		{
			draw_points(i);
			draw_line(i);
		}
	
	

}	

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);


	float WidthFactor = (float)w / 500;
	float HeightFactor = (float)h / 500;

	gluOrtho2D(0.0, 500 * WidthFactor, 500 * HeightFactor, 0.0);


	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON){
	
			points[point_num][0] = x;
			points[point_num][1] = y;

			draw_points(point_num);
			

		if (state == GLUT_UP) {
			draw_line(point_num);
			
			rubberband = true;

		}
		point_num++;

		
		
	}
}

void Motion(int x, int y)
{
	static GLint tmp_point[2];

	/// Logical Operation ON
	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_INVERT);

	
	if (!rubberband)
	{
		glBegin(GL_LINES);
		/// Erase Rubber-band
		glVertex2iv(points[point_num - 1]);
		glVertex2iv(tmp_point);
		glEnd();
		glFlush();
	}
	/// Draw new Rubber-band
	glBegin(GL_LINE_STRIP);
	glVertex2iv(points[point_num - 1]);
	glVertex2i(x, y);
	glEnd();
	glFlush();

	/// Logical Operation OFF
	glLogicOp(GL_COPY);
	glDisable(GL_COLOR_LOGIC_OP);

	/// Save Rubber-band point
	tmp_point[0] = x;
	tmp_point[1] = y;

	/// Erase Rubber-band
	rubberband = false;
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500,500);
	
	

	init();
	glutCreateWindow("Rubber-band");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();
	return 0;
}