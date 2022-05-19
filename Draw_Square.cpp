#include <GL/glut.h>
#include <stdlib.h>

void display(void) {
	// 흰색으로 설정
	glColor3f(1.0, 1.0, 1.0);

	//사각형의 좌표 입력
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 0.25, 0.0);
	glVertex3f(0.75, 0.25, 0.0);
	glVertex3f(0.75, 0.75, 0.0);
	glVertex3f(0.25, 0.75, 0.0);
	glEnd();

	// 이걸 사용하지 않으면 버퍼에만 쓰여져 있고 그려지지 않음.
	glFlush();	//사각형을 화면에 그림
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);	//색상 버퍼를 지움
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//직교 투영: left, right, bottom, top, near, far
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);	//GLUT 상태를 초기화


	// 디스플레이모드 형식 선택: Single buffer & RGBA color 모드 선택
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// 창의 크기와 위치 설정
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);

	// 윈도우 생성
	glutCreateWindow("01 사각형 그리기");
	init();

	//필요한 콜백 함수 등록: 매우 중요함, 경우도 알아두기
	// call back: 어떠한 상황이 발생하면 자동 호출 
	glutDisplayFunc(display);

	// 무한 이벤트 처리 루프
	// - 이벤트가 발생하면 일치하는 콜백 함수가 등록되어 있는 경우
	//등록된 함수가 자동으로 호출,, 맨 뒤에 꼭 있어야 함.
	glutMainLoop();	// 이벤트 처리 엔진 시작

	return 0;

}

/*
2022.03.16.
1. glClear: 버퍼를 지움.
- glClear(GLbitfield mask): 4개 버퍼.
- OR 연산자로 두 개 이상의 버퍼를 한꺼번에 지울 수 있음.

2. glColor 3f: 3f = RGB(float, 0.0 ~ 1.0)
- f대신 Suffix 여러개 사용가능. (ppt 참고)

3. glBegin(GLenum mode);, glEnd(void);
- 선, 점, 면 등을 그리기 위해 사용
- begin, end 사이에 정점 정보를 넣음.
ex) glBegin(GL_POLYGON);

*/