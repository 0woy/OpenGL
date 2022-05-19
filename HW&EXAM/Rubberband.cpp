#include <gl/glut.h>  
#include <stdio.h>
#define NUM 100//Set the number of vertices  

int alreadyFirstPoint = 0;//Mark whether the polyline has already been drawn  
int winWidth = 500, winHeight = 500;
int Mousex, Mousey;//Current mouse position  
int n = 0;//Record the number of polylines 

struct LineNode {//Define a line, including two points, four data
	int x1;
	int y1;
	int x2;
	int y2;
}Line[NUM];

void Initial(void)//Non-logic code, initialization
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//Set the window color  
}

void ChangeSize(int w, int h)//non-logic code, control window size
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);//Specify the window display area  
	glMatrixMode(GL_PROJECTION);//Specify and set projection parameters  
	glLoadIdentity();//Call the identity matrix, remove the previous projection parameter settings  
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);//Set projection parameters  
}

void PassiveMouseMove(GLint xMouse, GLint yMouse)//Non-logical code, correct mouse coordinates
{
	Mousex = xMouse;
	Mousey = winHeight - yMouse;
	glutPostRedisplay();
}

/*
The Display() method is the real way to draw lines
*/
void Display()
{
	int i, j;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Drawing in linear mode  
	glClear(GL_COLOR_BUFFER_BIT);//Fill the window with the current background color  
	glColor3f(0, 0, 0);//Specify the current drawing color  
	for (i = 0; i < n; i++) {//loop+glBegin maintains the line segment that has been drawn
		glBegin(GL_LINES);//Draw a straight line 
		//Set the two vertices of a line:
		glVertex2i(Line[i].x1, Line[i].y1);//Set the first point
		glVertex2i(Line[i].x2, Line[i].y2);//Set the second point
		glEnd();
	}
	if (alreadyFirstPoint == 1) {//After clicking the mouse, the second point of a line will move with the mouse
		glBegin(GL_LINES);
		if (n < NUM) {
			glVertex2i(Line[i].x1, Line[i].y1);//Determine the coordinates of the starting point
			glVertex2i(Mousex, Mousey);//The drop point follows the mouse movement
		}
		else {//When the two lines are drawn, stop the mouse rubber band and connect end to end to form a triangle
			glVertex2i(Line[0].x1, Line[0].y1);
			glVertex2i(Line[1].x2, Line[1].y2);
		}
		glEnd();
		//printf("Test\n");
	}
	glutSwapBuffers();//Swap buffer
}

/*
The function that controls the mouse drag, this code is the core of the rubber band
*/
void MouseDraw(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {//This line is an ordinary mouse button event
		if (alreadyFirstPoint == 0) {
			alreadyFirstPoint = 1;//Mark that the mouse clicked the first point
			Line[n].x1 = xMouse;
			Line[n].y1 = winHeight - yMouse;//correct the y coordinate
		}
		else {
			if (n < NUM) {//Artificial rules can only draw at most three lines
				Line[n].x2 = xMouse;
				Line[n].y2 = winHeight - yMouse;
				//printf("Test, you drew a new line segment\n");
				n++;//The number of polylines+1
			}
			//The second point of the polyline is used as the first point of the next line  
			Line[n].x1 = Line[n - 1].x2;
			Line[n].y1 = Line[n - 1].y2;
		}
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//Using double buffer and RGB model
	glutInitWindowSize(winWidth, winHeight);//Specify the size of the window  
	glutInitWindowPosition(100, 100);//Specify the position of the window on the screen  
	glutCreateWindow("Job 2-Interactive triangle drawing");//Create a window
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);//Specify window callback function  
	glutMouseFunc(MouseDraw);//Specify the mouse response function  
	glutPassiveMotionFunc(PassiveMouseMove);//Specify the mouse movement response function  
	Initial();//Start initialization
	glutMainLoop();//Start the main GLUT event processing loop  
	return 0;
}