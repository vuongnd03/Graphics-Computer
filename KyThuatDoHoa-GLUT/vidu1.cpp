//
// Ky thuat do hoa
// Ha Manh Toan hmtoan@ioit.ac.vn
//
#include <glut.h>
#include <math.h>

void display_vidu1() {
	// gán màu (r, g, b) => xanh lá cây
	glColor3f(0.0, 1.0, 0.0);
	// bắt đầu chế độ vẽ các đường thẳng
	glBegin(GL_LINES);	
	// T
	glVertex3f(-0.8, 0.3, 0.0);
	glVertex3f(-0.8, 0.7, 0.0);
	if (0) {
		glVertex3f(-0.9, 0.7, 0.0);
		glVertex3f(-0.7, 0.7, 0.0);

		// O
		glVertex3f(-0.6, 0.7, 0.0);
		glVertex3f(-0.4, 0.7, 0.0);

		glVertex3f(-0.4, 0.7, 0.0);
		glVertex3f(-0.4, 0.3, 0.0);

		glVertex3f(-0.4, 0.3, 0.0);
		glVertex3f(-0.6, 0.3, 0.0);

		glVertex3f(-0.6, 0.3, 0.0);
		glVertex3f(-0.6, 0.7, 0.0);

		// A
		glVertex3f(-0.3, 0.3, 0.0);
		glVertex3f(-0.2, 0.7, 0.0);

		glVertex3f(-0.2, 0.7, 0.0);
		glVertex3f(-0.1, 0.3, 0.0);

		glVertex3f(-0.25, 0.5, 0.0);
		glVertex3f(-0.15, 0.5, 0.0);

		// N
		glVertex3f(0.0, 0.3, 0.0);
		glVertex3f(0.0, 0.7, 0.0);

		glVertex3f(0.0, 0.7, 0.0);
		glVertex3f(0.2, 0.3, 0.0);

		glVertex3f(0.2, 0.3, 0.0);
		glVertex3f(0.2, 0.7, 0.0);

		// dau huyen
		glVertex3f(-0.25, 0.85, 0.0);
		glVertex3f(-0.15, 0.8, 0.0);
	}
	// Kết thúc chế độ vẽ
	glEnd(); // 
	// đẩy bộ nhớ vẽ ra
	glFlush();
}
int vidu1(int argc, char** argv) {
	// Khởi tạo cửa sổ
	glutInitWindowSize(250, 250); // kích thước
	glutInitWindowPosition(50, 50); // vị trí trên destop
	glutCreateWindow("rectangle"); // caption 
	// 
	glutDisplayFunc(display_vidu1); // đăng ký hàm callback hiển thị
	
	glutMainLoop(); // vòng lặp chính
	return 0;
}

















double goc(double degree) {
	return degree*3.14159265358979323846/180;
}

void nguGiac() {
	float a = 0.5;
	glBegin(GL_LINES);

	// AB
	glVertex3f(0, a, 0);
	glVertex3f(a*cos(goc(18)), a*sin(goc(18)), 0);
	// BC
	glVertex3f(a*cos(goc(18)), a*sin(goc(18)), 0);
	glVertex3f(a*sin(goc(36)), -a*cos(goc(36)), 0);
	// CD
	glVertex3f(a*sin(goc(36)), -a*cos(goc(36)), 0);
	glVertex3f(-a*sin(goc(36)), -a*cos(goc(36)), 0);
	// DE
	glVertex3f(-a*sin(goc(36)), -a*cos(goc(36)), 0);
	glVertex3f(-a*cos(goc(18)), a*sin(goc(18)), 0);
	// EA
	glVertex3f(-a*cos(goc(18)), a*sin(goc(18)), 0);
	glVertex3f(0, a, 0);
	// Kết thúc chế độ vẽ
	glEnd(); // 
}
void lucGiac() {
	float a = 0.5;
	glBegin(GL_LINES);
	// AB
	glVertex3f(a, 0, 0);
	glVertex3f(a/2, -a*sin(goc(60)), 0);
	// BC
	glVertex3f(a/2, -a*sin(goc(60)), 0);
	glVertex3f(-a/2, -a*sin(goc(60)), 0);
	// CD
	glVertex3f(-a/2, -a*sin(goc(60)), 0);
	glVertex3f(-a, 0, 0);
	// DE
	glVertex3f(-a, 0, 0);
	glVertex3f(-a/2, a*sin(goc(60)), 0);
	// EF
	glVertex3f(-a/2, a*sin(goc(60)), 0);
	glVertex3f(a/2, a*sin(goc(60)), 0);
	// FA
	glVertex3f(a/2, a*sin(goc(60)), 0);
	glVertex3f(a, 0, 0);
	glEnd();
}
void test_bai_2() {
	int n = 5;
	float v[] ={ 6., -3., 4.70727, 4.77929,-3.09075, 5.95376, -6.61746, -1.09966, -0.999068, -6.63339 };
	glBegin(GL_LINES);

	for (int i=0; i<n; i++) {
		glVertex3f(v[2*i]/10, v[2*i+1]/10, 0.0);
		glVertex3f(v[2*((i+1)%n)]/10, v[2*((i+1)%n)+1]/10, 0.0);
	}
	// Kết thúc chế độ vẽ
	glEnd(); // 
}