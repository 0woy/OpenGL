/*
빛의 약화

attenuation factor = 1 / (kc + kl d + kq d^2);

d: 조명과의 거리
kc: 상수 거리 (default = 1)
kl: 선형적으로 감소
kq: 2차함수로 감소.
default: 거리에 상관없이 밝음.


스포트라이트
- 스포트라이트 절단각: GL_SPOT_CUTOFF
- 스포트라이트 방향: GL_SPOT_DIRECTION
- 스포트라이트 감소인자: GL_SPOT_EXPONENT

법선 벡터의 정규화(법선벡터: 반시계로 감았을때 엄지손가락)
: 우리는 방향만 알면 되므로 크기는 모두 같게 해주는 것.
- 모든 법선벡터 자동으로 정규화
- glEnable(GL_NORMALIZE);

음영모드 정의
- FLAT Shading: glShadeModel(GL_FLAT)
(FAST, 하나의 색깔로 모두를 칠하는 것)
- Gouroud Shading: glShadeModel(GL_SMOOTH)


발광체: Emission
- 스스로 발광, 다른 물체에 빛을 내보내지 않음

조명모델 정의
- 전역 주변광: 광원에 무관하게 전체를 밝게.
ambient를 설정해주고 넣으면 됨.

- 양면 조명: 표면과 이면에 조명과 음영을 가하기 위함
GL_LIGHT_MODEL_TWO_SIDE: FALSE, TRUE

*/


#include <GL/glut.h>	
#include <stdio.h>

GLfloat position[] = { 0.0,4.5,0.0,1.0 };

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	GLfloat light_ambient[] = { 0.1,0.1,0.1,1.0 };
	GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);	
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	//감쇠율
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.001);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.004);

}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//조명 이동 적용
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, position);
		
	//조명의 위치를 cube로 출력
	glTranslated(position[0], position[1], position[2]);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 1.0, 1.0);
	glutWireCube(0.5);	

	glEnable(GL_LIGHTING);	
	glPopMatrix();

	glutSolidSphere(1, 50, 50);
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(
		-5.0, 5.0, 
		-5.0*(GLfloat)h / (GLfloat)w, 5.0*(GLfloat)w / (GLfloat)h,
		-5.0, 5.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void mouse(int button, int state, int x, int y) {
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			position[1] -= 0.1;
			printf("Lighting Postion: (%.2lf, %.2lf, %.2lf)\n",
				position[0], position[1], position[2]);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			position[1] += 0.1;
			printf("Lighting Postion: (%.2lf, %.2lf, %.2lf)\n",
				position[0], position[1], position[2]);
		}
		break;
	default:
		break;
	}

	glutPostRedisplay();
}



int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lighting Example");

	init();
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}