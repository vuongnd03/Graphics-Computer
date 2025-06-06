//
// Ky thuat do hoa
// Ha Manh Toan hmtoan@ioit.ac.vn
//
#include <glut.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "model.h"

namespace vd6 {
	Vector3 trans;
	Model* model, model1;
	int nPoints = 3;
	double angle =0;
	bool rotate = false;


	float x=0.0f, z=15.0f;
	void processSpecialKeys(int key, int xx, int yy) {

		float fraction = 0.1f;

		switch (key) {
		case GLUT_KEY_LEFT:
			x+=1;
			break;
		case GLUT_KEY_RIGHT:
			x-=1;
			break;
		case GLUT_KEY_UP:
			z += 1;
			break;
		case GLUT_KEY_DOWN:
			z -= 1;
			break;
		}
		glutPostRedisplay();
	}
	void init() {
		trans.x = 0;
		trans.y = 0;
		trans.z = 0;

		nPoints = 3;
		angle = 0;

		//model = new Model();
		//model = (Model*)malloc(sizeof(Model));
		//regularPolygon(model, 0.5, nPoints);
		model1.nVertices = 4;
		model1.vertices[0] = point3(-0.5, -0.5, 0);
		model1.vertices[1] = point3(-0.5, 0, 0.5);
		model1.vertices[2] = point3(-0.5, 0.5, 0);
		model1.vertices[3] = point3(0.5, -0.5, 0);
		model1.nEdges = 6;
		model1.edges[0][0] = 0;
		model1.edges[0][1] = 1;
		model1.edges[1][0] = 1;
		model1.edges[1][1] = 2;
		model1.edges[2][0] = 2;
		model1.edges[2][1] = 3;
		model1.edges[3][0] = 3;
		model1.edges[3][1] = 0;
		model1.edges[4][0] = 2;
		model1.edges[4][1] = 0;
		model1.edges[5][0] = 3;
		model1.edges[5][1] = 1;

		model = &model1;
		glClearColor(1.0, 1.0, 1.0, 1.0);
	}
	void display1() {
		glClear(GL_COLOR_BUFFER_BIT);


		glLoadIdentity();
		// Set the camera
		//printf("%lf %lf\n", x, z);
		gluLookAt(x, 0.0f, z,
			0, 0.0f, 0,
			0.0f, 1.0f, 0.0f);

		glColor3f(0.0, 0.0, 0.0);
		//drawModelLines(model);
		drawModelLines(model, trans);

		glFlush();
		//glutSwapBuffers();

		if (rotate) {
			angle = angle+0.0005;
			regularPolygon(model, 0.5, nPoints, angle);
		}
	}
	void processKeys(unsigned char key, int xx, int yy) {
		switch (key) {
		case 'w':
			z += 0.1;
			break;
		case 's':
			z -= 0.1;
			break;
		case 'a':
			x -= 0.1;
			break;
		case 'd':
			x += 0.1;
			break;
		case 'r':
			rotate = !rotate;
			break;
		case '>':
			nPoints++;
			regularPolygon(model, 0.5, nPoints);
			break;
		case '<':
			nPoints--;
			if (nPoints<3) nPoints = 3;
			regularPolygon(model, 0.5, nPoints);
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}
	void processMouse(int button, int state, int xx, int yy) {
		if (button==GLUT_LEFT_BUTTON && state==GLUT_UP) {
			
			glutPostRedisplay();
		} 
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
		gluPerspective(10.0f, ratio, 0.1f, 100.0f);
		//glOrtho(-100.f, 100.f, -100.f, 100.f, -100.f, 100.f);
		// quay lai ma tran model view
		glMatrixMode(GL_MODELVIEW);
	}
};
int vidu6(int argc, char** argv) {
	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(250, 250);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("rectangle");

	vd6::init();
	glutReshapeFunc(vd6::changeSize);
	glutDisplayFunc(vd6::display1);
	glutKeyboardFunc(vd6::processKeys);
	glutMouseFunc(vd6::processMouse);
	glutSpecialFunc(vd6::processSpecialKeys);
	glutIdleFunc(vd6::display1);
	glutMainLoop();

	free(vd6::model);
	return 0;
}