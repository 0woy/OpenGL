#include<GL/glut.h>
#include<stdlib.h>

void myinit() {
	GLfloat ambient[] = { 0.0,0.0,0.0,1.0 };
	GLfloat diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat lmodel_ambient[] = { 0.4,0.4,0.4,1.0 };
	GLfloat position[] = { 0.0,3.0,2.0,0.0 };
	GLfloat local_view[] = { 0.0 };

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Light0 조명 관련 정보
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	//전역 주면광 설정
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearColor(0.0, 0.1, 0.1, 0.0);

}


void display() {

	//재질 관련 정보
	GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
	GLfloat mat_ambient[] = { 0.7,0.7,0.7,1.0 };
	GLfloat mat_ambient_color[] = { 0.8,0.8,0.2,1.0 };
	GLfloat mat_diffuse[] = { 0.1,0.5,0.8,1.0 };
	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = { 0.3,0.2,0.2,0.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Fisrt row,
	// 재질에 diffuse만 있고, ambient, specular, shininess, emiision 없음
	glPushMatrix();
	glTranslatef(-3.75, 3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();


	// diffuse, specular O / shine = low / Ambient, emiision X
	glPushMatrix();
	glTranslatef(-1.25, 3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();


	// diffuse, specular O / Shine = high / Ambient, Emission X
	glPushMatrix();
	glTranslatef(1.25, 3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// diffuse, Emission O / Shine  Ambient, Specular X
	glPushMatrix();
	glTranslatef(3.75, 3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// Second Row
	// Ambient, diffuse 0 / Specular, Shininess, Emissoion X
	glPushMatrix();
	glTranslatef(-3.75, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// diffuse, specular, Ambient O / Shine = low / Emission X
	glPushMatrix();
	glTranslatef(-1.25, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// diffuse, specular Ambient O / Shine = high / Emission X
	glPushMatrix();
	glTranslatef(1.25, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// diffuse, Ambient, Emission O / Shine, Specular X
	glPushMatrix();
	glTranslatef(3.75, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();



	//Third Row
	// diffuse, Colored Ambient O / Shine, Specular, Emission X
	glPushMatrix();
	glTranslatef(-3.75, -3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();

	// diffuse, Colored Ambient, Specular O / Shine =low / Emission X
	glPushMatrix();
	glTranslatef(-1.25, -3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();


	// diffuse, Colored Ambient, Specular O / Shine =high/ Emission X
	glPushMatrix();
	glTranslatef(1.25, -3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();


	// diffuse, Colored Ambient, Emission O / Shine, Specular X
	glPushMatrix();
	glTranslatef(3.75, -3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();


	glFlush();

}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= (h*2))
		glOrtho(-6.0, 6.0, -3.0*((GLfloat)h*2) / (GLfloat)w,
			3.0*((GLfloat)h * 2) / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-6.0*(GLfloat)w / ((GLfloat)h*2), 
			6.0*(GLfloat)w / ((GLfloat)h * 2),
			-3.0, 3.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {

	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:
		return;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Material Color");

	myinit();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;

}