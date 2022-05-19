#include<stdlib.h>
#include<GL/glut.h>
#include<GL/GL.h>
#include<GL/GLU.h>

GLboolean IsSphere = true;
GLboolean IsSmall = true;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0, 0.5);
	if ((IsSphere) && (IsSmall))
		glutWireSphere(0.2, 15, 15);

	else if ((IsSphere) && (!IsSmall))
		glutWireSphere(0.4, 15, 15);
	else if ((!IsSphere) && (IsSmall))
		glutWireTorus(0.1, 0.3, 40, 20);
	else
		glutWireTorus(0.2, 0.5, 40, 20);

	glFlush();
}


void main_menu(int v) {
	if (v == 1)
		IsSphere = true;
	else if (v == 2)
		IsSphere = false;
	else if (v == 3)
		exit(0);
	glutPostRedisplay();
}

void sub_menu(int v) {
	if (v == 1)
		IsSmall = true;
	else if (v == 2)
		IsSmall = false;
	glutPostRedisplay();
}


int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sub menu example");

	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	GLint MySubMenuID = glutCreateMenu(sub_menu);
	glutAddMenuEntry("Small obj", 1);
	glutAddMenuEntry("Big obj", 2);


	// addMenu, addSub인지에 따라 달라짐.
	GLint MyMainMenuID = glutCreateMenu(main_menu);
	glutAddMenuEntry("Draw Sphere", 1);
	glutAddMenuEntry("Draw Torus", 2);
	glutAddSubMenu("Change Size", MySubMenuID);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;




}