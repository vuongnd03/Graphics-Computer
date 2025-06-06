////
//// Ky thuat do hoa
//// Ha Manh Toan hmtoan@ioit.ac.vn
////
//#include <glut.h>
//#include <stdio.h>
//
//const int N = 26;
//double shape[N][2] = {
//	{ -0.8, 0.3 },
//	{ -0.8, 0.7 },
//	{ -0.9, 0.7 },
//	{ -0.7, 0.7 },
//	{ -0.6, 0.7 },
//	{ -0.4, 0.7 },
//	{ -0.4, 0.7 },
//	{ -0.4, 0.3 },
//	{ -0.4, 0.3 },
//	{ -0.6, 0.3 },
//	{ -0.6, 0.3 },
//	{ -0.6, 0.7 },
//	{ -0.3, 0.3 },
//	{ -0.2, 0.7 },
//	{ -0.2, 0.7 },
//	{ -0.1, 0.3 },
//	{ -0.25, 0.5 },
//	{ -0.15, 0.5 },
//	{ 0.0, 0.3 },
//	{ 0.0, 0.7 },
//	{ 0.0, 0.7 },
//	{ 0.2, 0.3 },
//	{ 0.2, 0.3 },
//	{ 0.2, 0.7 },
//	{ -0.25, 0.85 },
//	{ -0.15, 0.8 } 
//};
//double sx=1, sy=1;
//// Với điểm i trong shape, tọa độ mới 
//// [shape[i].x*sx  shape[i].y*sy]
//// Chúng ta vẽ bằng glVertex3f <- tọa độ mới 
//
//const int N_COLORS = 3;
//double colors[N_COLORS][3] ={
//	{0.0, 0.0, 1.0},
//	{0.0, 1.0, 0.0},
//	{1.0, 0.0, 0.0}
//};
//int colorIdx = 0;
//
//void draw1() {
//	glColor3f(colors[colorIdx][0], 
//		colors[colorIdx][1], 
//		colors[colorIdx][2]);
//	glBegin(GL_LINES);
//
//	for (int i=0; i<N/2; i++) {
//		glVertex3f(shape[i*2][0]*sx, shape[i*2][1]*sy, 0);
//		glVertex3f(shape[i*2+1][0]*sx, shape[i*2+1][1]*sy, 0);
//	}
//
//	glEnd();
//}
//void display1() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	draw1();	
//	glFlush();
//}
//void processKeys(unsigned char key, int x, int y) {
//	switch (key) {
//	case 'w':
//		sy += 0.1;
//		break;
//	case 's':
//		sy -= 0.1;
//		break;
//	case 'a':
//		sx -= 0.1;
//		break;
//	case 'd':
//		sx += 0.1;
//		break;
//	default:
//		break;
//	}
//	glutPostRedisplay();
//}
//void processMouse(int button, int state, int x, int y) {
//	if (button==GLUT_LEFT_BUTTON && state==GLUT_UP) {
//		colorIdx = (colorIdx+1)%N_COLORS;
//		glutPostRedisplay();
//	}
//}
///*
//	1. Đăng ký hàm callback cho sự kiện phím, chuột 
//		=> cái thư viện cho
//	- glutKeyboardFunc -> phím
//	- glutMouseFunc-> chuột
//	Bạn phải viết hàm callback
//	- processKeys
//	- processMouse
//	2. Biến đổi ma trận
//	- Trong ví dụ, tự thực hiện phép cộng ma trận
//		trong tham số của hàm glVertex3f (phần +tx và +ty)
//	- Xây dựng cụ thể phép toán bằng các đối tượng:
//		tạo lớp:
//		class Matrix {
//		public:
//			void add(const Matrix& m) {...}
//		};
//		hoặc hàm:
//		Matrix add(const Matrix& A, const Matrix& B) {...}
//		Thường các đối tượng ma trận, ... 
//			=> các thư viện sẽ có hỗ trợ sẵn
//*/
//int vidu2(int argc, char** argv) {
//	glutInitWindowSize(250, 250);
//	glutInitWindowPosition(50, 50);
//	glutCreateWindow("rectangle");
//
//	glutDisplayFunc(display1);
//	glutKeyboardFunc(processKeys);
//	glutMouseFunc(processMouse);
//
//	glutMainLoop();
//	return 0;
//}