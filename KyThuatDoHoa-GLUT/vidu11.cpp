//
// Ky thuat do hoa
// Ha Manh Toan hmtoan@ioit.ac.vn
//
#include <glut.h>

namespace vd11 {
	float lightDiffuse[] ={ 0.0, 1.0, 0.0, 1.0 };  // xanh la cay
	float lightPosition[] ={ 0.0, 1.0, 1.0, 0.0 };  // vi tri nguon sang
	float n[6][3];   // phap tuyen 6 be mat hinh lap phuong
	int faces[6][4] ={  // chi so cac dinh cua 6 mat hinh lap phuong
		{ 0, 1, 2, 3 },{ 3, 2, 6, 7 },{ 7, 6, 5, 4 },
		{ 4, 5, 1, 0 },{ 5, 6, 2, 1 },{ 7, 4, 0, 3 } };
	float nv[8][3];  //  phap tuyen 6 dinh hinh lap phuong
	float v[8][3];  // toa do 8 dinh hinh lap phuong
	float angle = 0;
	void drawBox() {
		glPushMatrix();
		glRotatef(angle, 1, 0, 0);
		glBegin(GL_QUADS);
		for (int i = 0; i < 6; i++) {
			glNormal3fv(&nv[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glNormal3fv(&nv[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glNormal3fv(&nv[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glNormal3fv(&nv[faces[i][3]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
		}
		glEnd();
		glPopMatrix();
		angle +=0.02;
	}
	void drawBox1() {
		glPushMatrix();
		glRotatef(angle, 1, 0, 0);
		glBegin(GL_QUADS);
		for (int i = 0; i < 6; i++) {
			glNormal3fv(&n[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
		}
		glEnd();
		glPopMatrix();
		angle +=0.02;
	}

	void display() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//drawBox1();
		//drawBox();
		//glutSolidCube(2);
		//glutSolidSphere(1.5, 10, 10);
		{
			glPushMatrix();
			glRotatef(angle, 1, 0, 0);
			glutSolidTorus(0.5, 0.7, 8, 15);
			glPopMatrix();
			angle +=0.02;
		}
		glFlush();
		//glutSwapBuffers();
	}

	void init() {
		// gan toa do 8 dinh
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
		v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
		v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
		v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
		v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
		// phap tuyen 8 dinh
		nv[0][0] = nv[1][0] = nv[2][0] = nv[3][0] = -1;
		nv[4][0] = nv[5][0] = nv[6][0] = nv[7][0] = 1;
		nv[0][1] = nv[1][1] = nv[4][1] = nv[5][1] = -1;
		nv[2][1] = nv[3][1] = nv[6][1] = nv[7][1] = 1;
		nv[0][2] = nv[3][2] = nv[4][2] = nv[7][2] = 1;
		nv[1][2] = nv[2][2] = nv[5][2] = nv[6][2] = -1;
		for (int i=0; i<6; i++) {
			for (int j=0; j<3; j++) {
				if (v[faces[i][0]][j]==v[faces[i][1]][j] &&
					v[faces[i][0]][j]==v[faces[i][2]][j] &&
					v[faces[i][0]][j]==v[faces[i][3]][j]) {
					n[i][j] = v[faces[i][0]][j];
					break;
				}
			}
		}

		// enable viec chieu sang
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);

		glEnable(GL_DEPTH_TEST);
	}
	void changeSize(int w, int h) {
		if (h == 0) h = 1;
		float ratio = w * 1.0 / h;
		// su dung ma tran phep chieu
		glMatrixMode(GL_PROJECTION);
		// Cap nhat ve ma tran don vi
		glLoadIdentity();
		// Thiet lap viewport
		glViewport(0, 0, w, h);
		// thiet lap phep chieu
		gluPerspective(45.0f, ratio, 1.f, 10.0f);
		//glOrtho(-100.f, 100.f, -100.f, 100.f, -100.f, 100.f);
		// quay lai ma tran model view
		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		gluLookAt(0.0, 0.0, 5.0,
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.);

		glTranslatef(0.0, 0.0, -1.0);
		glRotatef(60, 1.0, 0.0, 0.0);
		glRotatef(-20, 0.0, 0.0, 1.0);
	}
}
int vidu11(int argc, char **argv) {
	glutInitDisplayMode( GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(30, 30);
	glutCreateWindow("opengl");

	glutReshapeFunc(vd11::changeSize);
	glutDisplayFunc(vd11::display);
	glutIdleFunc(vd11::display);
	vd11::init();
	glutMainLoop();
	return 0;     
}



//#include "glut.h"
//namespace vd11 {
//static double spin = 0;
//
//void init(void) {
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glShadeModel(GL_SMOOTH);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glEnable(GL_DEPTH_TEST);
//}
//
//void display(void) {
//	GLfloat position[] ={ 0.0, 0.0, 1.5, 1.0 };
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glPushMatrix();
//	glTranslatef(0.0, 0.0, -5.0);
//
//	glPushMatrix();
//	glRotated((GLdouble)spin, 1.0, 0.0, 0.0);
//	glLightfv(GL_LIGHT0, GL_POSITION, position);
//
//	glTranslated(0.0, 0.0, 1.5);
//	glDisable(GL_LIGHTING);
//	glColor3f(0.0, 1.0, 1.0);
//	glutWireCube(0.1);
//	glEnable(GL_LIGHTING);
//	glPopMatrix();
//
//	glutSolidTorus(0.275, 0.85, 8, 15);
//	glPopMatrix();
//	glFlush();
//	spin = (spin + 0.1);
//}
//
//void reshape(int w, int h) {
//	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(40.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//void mouse(int button, int state, int x, int y) {
//	switch (button) {
//	case GLUT_LEFT_BUTTON:
//		if (state == GLUT_DOWN) {
//			spin = (spin + 30);// % 360;
//			glutPostRedisplay();
//		}
//		break;
//	default:
//		break;
//	}
//}
//}
//int vidu11(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(500, 500);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow(argv[0]);
//	vd11::init();
//	glutDisplayFunc(vd11::display);
//	glutIdleFunc(vd11::display);
//	glutReshapeFunc(vd11::reshape);
//	glutMouseFunc(vd11::mouse);
//	glutMainLoop();
//	return 0;
//}