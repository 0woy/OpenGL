//22.04.04.
//평행투영: 원근법 적용X
//CLIP: viewing 박스 안에 있는 물체만 그리는 것, 바깥에 있으면 잘림

#include<GL/glut.h>
#include<stdlib.h>

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();

	/* Viewing Transformation */
	// upx,y,z : 카메라의 가로, 세로, Z
	gluLookAt(5.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	/* Modeling Transformation */
	glScalef(1.0, 2.0, 1.0);
	glutWireCube(1.0);
	//물체를 커지게 하는 방법: 크기를 키운다, 카메라의 위치를 가까이한다(in Perspective view)

	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	//glViewport(100,200,400, 300);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //행렬 초기화
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Transformed Cube");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}



