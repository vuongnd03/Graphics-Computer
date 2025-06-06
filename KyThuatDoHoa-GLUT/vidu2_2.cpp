//
// Ky thuat do hoa
// Ha Manh Toan hmtoan@ioit.ac.vn
//
#include <glut.h>
#include <stdio.h>
#include <math.h>

const int N = 26;
double shape[N][2] = {
	{ -0.8, 0.3 },
	{ -0.8, 0.7 },
	{ -0.9, 0.7 },
	{ -0.7, 0.7 },
	{ -0.6, 0.7 },
	{ -0.4, 0.7 },
	{ -0.4, 0.7 },
	{ -0.4, 0.3 },
	{ -0.4, 0.3 },
	{ -0.6, 0.3 },
	{ -0.6, 0.3 },
	{ -0.6, 0.7 },
	{ -0.3, 0.3 },
	{ -0.2, 0.7 },
	{ -0.2, 0.7 },
	{ -0.1, 0.3 },
	{ -0.25, 0.5 },
	{ -0.15, 0.5 },
	{ 0.0, 0.3 },
	{ 0.0, 0.7 },
	{ 0.0, 0.7 },
	{ 0.2, 0.3 },
	{ 0.2, 0.3 },
	{ 0.2, 0.7 },
	{ -0.25, 0.85 },
	{ -0.15, 0.8 } 
};
double alpha=0;

const int N_COLORS = 7;
double colors[N_COLORS][3] ={
	{0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0},
	{1.0, 0.0, 0.0},
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 0.0, 1.0 },
	{ 0.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0 }
};
int colorIdx = 0;

#define xrot(x, y) x*cos(alpha)-y*sin(alpha)
#define yrot(x, y) x*sin(alpha)+y*cos(alpha)
void draw1() {
	glColor3f(colors[colorIdx][0],
		colors[colorIdx][1],
		colors[colorIdx][2]);
	glBegin(GL_LINES);

	//// vẽ trực tiếp đối tượng
	//for (int i=0; i<N/2; i++) {
	//	glVertex3f(shape[i*2][0], shape[i*2][1], 0);
	//	glVertex3f(shape[i*2+1][0], shape[i*2+1][1], 0);
	//}

	// x = x+alpha; y=y+alpha
	for (int i=0; i<N/2; i++) {
		glVertex3f(shape[i*2][0]+alpha, shape[i*2][1]+alpha, 0);
		glVertex3f(shape[i*2+1][0]+alpha, shape[i*2+1][1]+alpha, 0);
	}

	//for (int i=0; i<N/2; i++) {
	//	glVertex3f(xrot(shape[i*2][0], shape[i*2][1]), yrot(shape[i*2][0], shape[i*2][1]), 0);
	//	glVertex3f(xrot(shape[i*2+1][0], shape[i*2+1][1]), yrot(shape[i*2+1][0], shape[i*2+1][1]), 0);
	//}

	glEnd();
}
void display1() {
	glClear(GL_COLOR_BUFFER_BIT);// xóa màn hình
	draw1();	
	glFlush();
}
void processKeys(unsigned char key, int x, int y) {
	switch (key) { // kiểm tra mã phím
	case 'a': //xử lý với từng trường hợp
		alpha -= 0.1;
		break;
	case 'd':
		alpha += 0.1;
		break;
	default:
		break;
	}
	glutPostRedisplay(); // vẽ lại
}
// colorIdx cần phải trong phạm vi [0,1,..., N_COLORS-1]
void processMouse(int button, int state, int x, int y) {
	if (button==GLUT_LEFT_BUTTON && state==GLUT_UP) {
		colorIdx = (colorIdx+1)%N_COLORS;
		glutPostRedisplay();
	}
}
int vidu2(int argc, char** argv) {
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("rectangle");

	glutDisplayFunc(display1);
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouse);

	glutMainLoop();
	return 0;
}