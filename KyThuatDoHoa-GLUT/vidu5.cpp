//
// Ky thuat do hoa
// Ha Manh Toan hmtoan@ioit.ac.vn
//
#include <glut.h>
#include <stdio.h>
#include <malloc.h>
#include "model.h"

namespace vd5 {
	Vector3 trans;
	Model* model;
	int nPoints = 3;
	double angle =0;
	bool rotate = false;


	void init() {
		trans.x = 0;
		trans.y = 0;
		trans.z = 0;

		nPoints = 6;
		angle = 0;

		//model = new Model();
		model = (Model*)malloc(sizeof(Model));
		//regularPolygon(model, 0.5, nPoints);
		regularPolygon(model, nPoints, 0.5, 0);

		glClearColor(1.0, 1.0, 1.0, 1.0);
	}
	void display1() {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 1.0, 0.0);
		//drawModelLines(model);
		drawModelLines(model, trans);

		glFlush();
		//glutSwapBuffers();

		if (rotate) {
			angle = angle+0.0005;
			regularPolygon(model, 0.5, nPoints, angle);
		}
	}
	void processKeys(unsigned char key, int x, int y) {
		switch (key) {
		case 'w':
			trans.y += 0.1;
			break;
		case 's':
			trans.y -= 0.1;
			break;
		case 'a':
			trans.x -= 0.1;
			break;
		case 'd':
			trans.x += 0.1;
			break;
		case 'r':
			rotate = !rotate;
			break;
		case '>':
			nPoints++;
			//regularPolygon(model, 0.5, nPoints);
			regularPolygon(model, nPoints, 0.5, 0);
			break;
		case '<':
			nPoints--;
			if (nPoints<3) nPoints = 3;
			//regularPolygon(model, 0.5, nPoints);
			regularPolygon(model, nPoints, 0.5, 0);
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}
	void processMouse(int button, int state, int x, int y) {
		if (button==GLUT_LEFT_BUTTON && state==GLUT_UP) {
			
			glutPostRedisplay();
		} 
	}
};

int vidu5(int argc, char** argv) {
	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(250, 250);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("rectangle");

	vd5::init();
	glutDisplayFunc(vd5::display1);
	glutKeyboardFunc(vd5::processKeys);
	glutMouseFunc(vd5::processMouse);
	glutIdleFunc(vd5::display1);
	glutMainLoop();

	free(vd5::model);
	return 0;
}