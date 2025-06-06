//
// Ky thuat do hoa
// Ha Manh Toan hmtoan@ioit.ac.vn
//
#include <glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include <conio.h>

namespace vd8 {
	float lx=0.0f, ly=0.0f;
	float x=0.0f, y=0.0f;
	float angle = 0.f;

	Model pyramid, tile, cone;

	void printMatrix() {
		GLfloat matrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++) {
				printf("%.2f\t", matrix[i*4+j]);
			}
			printf("\n");
		}
		printf("\n");
		_getch();
	}

	void changeSize(int w, int h) {
		if (h == 0) h = 1;
		float ratio = w * 1.0 / h;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, w, h);
		gluPerspective(45.0f, ratio, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
	}

	void makePyramid(Model* m) {
		m->nVertices = 5;
		m->vertices[0] = point3(-1, -1, 0);
		m->vertices[1] = point3(-1, 1, 0);
		m->vertices[2] = point3(1, 1, 0);
		m->vertices[3] = point3(1, -1, 0);
		m->vertices[4] = point3(0, 0, 1);

		m->nEdges = 8;
		m->edges[0][0] = 0; m->edges[0][1] = 1;
		m->edges[1][0] = 1; m->edges[1][1] = 2;
		m->edges[2][0] = 2; m->edges[2][1] = 3;
		m->edges[3][0] = 3; m->edges[3][1] = 0;
		m->edges[4][0] = 4; m->edges[4][1] = 1;
		m->edges[5][0] = 4; m->edges[5][1] = 2;
		m->edges[6][0] = 4; m->edges[6][1] = 3;
		m->edges[7][0] = 4; m->edges[7][1] = 0;
	}

	void makeTile(Model* m) {
		m->nVertices = 4;
		m->vertices[0] = point3(-0.5, -0.5, 0);
		m->vertices[1] = point3(-0.5, 0.5, 0);
		m->vertices[2] = point3(0.5, 0.5, 0);
		m->vertices[3] = point3(0.5, -0.5, 0);

		m->nEdges = 4;
		m->edges[0][0] = 0; m->edges[0][1] = 1;
		m->edges[1][0] = 1; m->edges[1][1] = 2;
		m->edges[2][0] = 2; m->edges[2][1] = 3;
		m->edges[3][0] = 3; m->edges[3][1] = 0;
	}

	void makeCone(Model* m) {
		regularPolygon(m, 1, 10);
		m->nVertices+=1;
		m->vertices[m->nVertices-1] = point3(0, 0, 1);
		int k = m->nEdges;
		m->nEdges *=2;
		for (int i=0; i<m->nVertices; i++) {
			m->edges[k+i][0] = m->nVertices-1;
			m->edges[k+i][1] = i;
		}
	}

	void init() {
		makePyramid(&pyramid);
		makeTile(&tile);
		makeCone(&cone);

		lx = cos(angle);
		ly = sin(angle);
	}

	void drawGround() {
		glLineWidth(1.0f);
		glColor3f(0.9, 0.9, 0.9);
		for (int x=-100; x<100; x+=1) {
			for (int y=-100; y<100; y+=1) {
				glPushMatrix();
				glTranslatef(1.0*x, 1.0*y, 0.f);
				drawModelLines(&tile);
				glPopMatrix();
			}
		}
	}
	double scale = 0.5, scaleStep = 0.01;
	double objRot = 0;
	void drawObjects() {
		glLineWidth(2.0f);
		int idxColor = 0;
		for (int x=-50; x<50; x+=7) {
			for (int y=-50; y<50; y+=7) {
				glColor3f(idxColor%3==0, idxColor%3==1, idxColor%3==2);
				
				glPushMatrix();
				glTranslatef(x, y, 0);
				glRotatef(objRot, 1, 1, 1);
				glScalef(1, 1, scale);

				if (idxColor%2==0) drawModelLines(&pyramid);
				else drawModelLines(&cone);

				glPopMatrix();
				idxColor++;
			}
		}
		scale += scaleStep;
		if (scale<0.5|| scale>3) scaleStep *= -1;
		objRot += 1;
		if (objRot>360) objRot -= 360;
	}

	void display(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		if (0) {
			printf("Ma tran don vi:\n");
			printMatrix();
			printf("dich (10, 20, 30)\n");
			glTranslatef(10, 20, 30);
			printMatrix();
			printf("xoay quanh truc (0,0,1) 1 goc=30 do\n");
			printf("sin(30 do)=%lf\ncos(30 do)=%lf\n", sin(M_PI/6), cos(M_PI/6));
			glRotatef(30, 0, 0, 1);
			printMatrix();
			printf("co dan (2, 3, 4)\n");
			glScalef(2, 3, 4);
			printMatrix();
			glLoadIdentity();
		}
		gluLookAt(x, y, 1.0f,
			x+lx, y+ly, 1.0f,
			0.0f, 0.0f, 1.0f);

		drawGround();
		
		drawObjects();

		//glutSwapBuffers();
		glFlush();
	}

	void processNormalKeys(unsigned char key, int x, int y) {

		//if (key == 27)
		//	exit(0);
	}

	void processSpecialKeys(int key, int xx, int yy) {

		float fraction = 0.1f;

		switch (key) {
		case GLUT_KEY_LEFT:
			angle += 0.01f;
			lx = cos(angle);
			ly = sin(angle);
			break;
		case GLUT_KEY_RIGHT:
			angle -= 0.01f;
			lx = cos(angle);
			ly = sin(angle);
			break;
		case GLUT_KEY_UP:
			x += lx * fraction;
			y += ly * fraction;
			break;
		case GLUT_KEY_DOWN:
			x -= lx * fraction;
			y -= ly * fraction;
			break;
		}
		//glutPostRedisplay();
	}
};
int vidu8(int argc, char **argv) {

	// init GLUT and create window

	//glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH/* | GLUT_DOUBLE | GLUT_RGBA*/);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("opengl");
	vd8::init();
	// register callbacks
	glutDisplayFunc(vd8::display);
	glutReshapeFunc(vd8::changeSize);
	glutIdleFunc(vd8::display);
	glutKeyboardFunc(vd8::processNormalKeys);
	glutSpecialFunc(vd8::processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

