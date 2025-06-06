//
// Ky thuat do hoa
// Ha Manh Toan hmtoan@ioit.ac.vn
//
#include <glut.h>
#include <stdio.h>
#include <malloc.h>
#include "model.h"

namespace vd4 {
	Model *model1, *model2, *model;

	double alpha = 0;
	double step = 0.0002;
	void init() {
		model1 = (Model*)malloc(sizeof(Model));
		model1->nVertices = 4;
		model1->vertices[0] = point3(-0.5, -0.5, 0);
		model1->vertices[1] = point3(-0.5, 0, 0);
		model1->vertices[2] = point3(-0.5, 0.5, 0);
		model1->vertices[3] = point3(0.5, -0.5, 0);

		/*model1->vertices[0] = point3(-0.15, 0.15, 0);
		model1->vertices[1] = point3(-0.5, 0.5, 0);
		model1->vertices[2] = point3(0.15, -0.15, 0);
		model1->vertices[3] = point3(0.5, -0.5, 0);*/
		model1->nEdges = 4;
		model1->edges[0][0] = 0;
		model1->edges[0][1] = 1;
		model1->edges[1][0] = 1;
		model1->edges[1][1] = 2;
		model1->edges[2][0] = 2;
		model1->edges[2][1] = 3;
		model1->edges[3][0] = 3;
		model1->edges[3][1] = 0;

		model2 = (Model*)malloc(sizeof(Model));
		model2->nVertices = 4;
		model2->vertices[0] = point3(-0.5, -0.5, 0);
		model2->vertices[1] = point3(-0.5, 0.5, 0);
		model2->vertices[2] = point3(0.5, 0.5, 0);
		model2->vertices[3] = point3(0.5, -0.5, 0);
		model2->nEdges = 4;
		model2->edges[0][0] = 0;
		model2->edges[0][1] = 1;
		model2->edges[1][0] = 1;
		model2->edges[1][1] = 2;
		model2->edges[2][0] = 2;
		model2->edges[2][1] = 3;
		model2->edges[3][0] = 3;
		model2->edges[3][1] = 0;

		model = (Model*)malloc(sizeof(Model));
		model->nVertices = 4;
		model->vertices[0] = point3(-0.5, -0.5, 0);
		model->vertices[1] = point3(-0.5, 0.5, 0);
		model->vertices[2] = point3(0.5, 0.5, 0);
		model->vertices[3] = point3(0.5, -0.5, 0);
		model->nEdges = 4;
		model->edges[0][0] = 0;
		model->edges[0][1] = 1;
		model->edges[1][0] = 1;
		model->edges[1][1] = 2;
		model->edges[2][0] = 2;
		model->edges[2][1] = 3;
		model->edges[3][0] = 3;
		model->edges[3][1] = 0;
		glClearColor(1.0, 1.0, 1.0, 1.0);
	}
	void display1() {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 0.0, 0.0);
		drawModelLines(model);

		glFlush();
		//glutSwapBuffers();

		for (int i=0; i<model->nVertices; i++) {
			model->vertices[i].x = alpha*model1->vertices[i].x+(1-alpha)*model2->vertices[i].x;
			model->vertices[i].y = alpha*model1->vertices[i].y+(1-alpha)*model2->vertices[i].y;
			model->vertices[i].z = alpha*model1->vertices[i].z+(1-alpha)*model2->vertices[i].z;
		}
		alpha += step;
		if (alpha>1) {
			alpha = 1;
			step = -step;
		} else if (alpha<0){
			alpha=0;
			step=-step;
		}
	}
	void processKeys(unsigned char key, int x, int y) {
		switch (key) {
		case 'w':
			
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
int vidu4(int argc, char** argv) {
	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(250, 250);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("rectangle");

	vd4::init();
	glutDisplayFunc(vd4::display1);
	glutKeyboardFunc(vd4::processKeys);
	glutMouseFunc(vd4::processMouse);
	glutIdleFunc(vd4::display1);
	glutMainLoop();

	free(vd4::model);
	return 0;
}