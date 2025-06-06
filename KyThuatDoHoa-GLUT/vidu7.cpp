//
// Ky thuat do hoa
// Ha Manh Toan hmtoan@ioit.ac.vn
//
#include <glut.h>
#include <math.h>
#include <stdio.h>
#include "model.h"

namespace vd7 {
	float lx=0.0f, ly=0.0f;
	float x=0.0f, y=0.0f;
	float angle = 0.f;

	Model pyramid, tile, cone, cone1;

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
		regularPolygon(m, 1, 5);
		m->nVertices+=1;
		m->vertices[m->nVertices-1] = point3(0, 0, 1);
		int k = m->nEdges;
		m->nEdges *=2;
		for (int i=0; i<m->nVertices; i++) {
			m->edges[k+i][0] = m->nVertices-1;
			m->edges[k+i][1] = i;
		}
	}

	void makeCone1(Model* m) {
		//Nón => đáy hình tròn + chóp ~ đáy đa giác đều + chóp
		//Tạo hình nón:
		//N: số cạnh của đa giác đều
		int N = 7;

		//Tạo M1: đa giác đều N cạnh
		Model m1;
		regularPolygon(&m1, 0.5, N);

		//Cone:
		//  Số đỉnh: N + 1
		m->nVertices = N+1;
		//  Các đỉnh: các đỉnh của đa giác đều + đỉnh chóp
		// => duyệt tất cả các đỉnh của đa giác đều, gán vào hình nón
		for (int i=0; i<N; i++) {
			m->vertices[i] = m1.vertices[i];
		}
		//    thêm đỉnh chóp
		m->vertices[N] = point3(0, 0, 1);

		//  Số cạnh: 2n
		m->nEdges = 2*N;

		//  Các cạnh: các cạnh ở đáy + các cạnh nối đỉnh ở đáy với chóp
		//  bước 1: thêm các cạnh ở đáy => N cạnh đầu tiên: 0..N-1
		for (int i=0; i<N; i++) {
			m->edges[i][0] = m1.edges[i][0];
			m->edges[i][1] = m1.edges[i][1];
		}
		//  bước 2: thêm các cạnh nối đỉnh ở đáy với chóp => N cạnh tiếp theo: N..(2N-1)
		for (int i=0; i<N; i++) {
			m->edges[N+i][0] = i;
			m->edges[N+i][1] = N;
		}
	}

	void init() {
		makePyramid(&pyramid);
		//makeTile(&tile);
		makeCone(&cone);
		makeCone1(&cone1);

		lx = cos(angle);
		ly = sin(angle);
	}

	void drawGround() {
		glColor3f(0.9, 0.9, 0.9);
		for (int x=-100; x<100; x+=1) {
			for (int y=-100; y<100; y+=1) {
				//drawModelLines(&tile, point3(x, y, 0));


				glBegin(GL_LINE_STRIP);
				glVertex3f(x-0.5, y-0.5, 0);
				glVertex3f(x-0.5, y+0.5, 0);
				glVertex3f(x+0.5, y+0.5, 0);
				glVertex3f(x+0.5, y-0.5, 0);
				glVertex3f(x-0.5, y-0.5, 0);
				glEnd();
			}
		}
	}
	void drawGroundQuads() {
		int idxColor = 0;
		for (int x=-100; x<100; x+=1) {
			for (int y=-100; y<100; y++) {
				glColor3f(idxColor%3==0, idxColor%3==1, idxColor%3==2);
				glBegin(GL_QUADS);
				glVertex3f(x-0.5, y-0.5, 0);
				glVertex3f(x-0.5, y+0.5, 0);
				glVertex3f(x+0.5, y+0.5, 0);
				glVertex3f(x+0.5, y-0.5, 0);
				glEnd();
				idxColor++;
			}
		}
	}
	void drawGroundQuads1() {
		int idxColor = 0;
		for (int x=-100; x<100; x+=1) {
			for (int y=-100; y<100; y++) {
				glBegin(GL_QUADS);
				idxColor++;
				glColor3f(idxColor%3==0, idxColor%3==1, idxColor%3==2);
				glVertex3f(x-0.5, y-0.5, 0);
				idxColor++;
				glColor3f(idxColor%3==0, idxColor%3==1, idxColor%3==2);
				glVertex3f(x-0.5, y+0.5, 0);
				idxColor++;
				glColor3f(idxColor%3==0, idxColor%3==1, idxColor%3==2);
				glVertex3f(x+0.5, y+0.5, 0);
				idxColor++;
				glColor3f(idxColor%3==0, idxColor%3==1, idxColor%3==2);
				glVertex3f(x+0.5, y-0.5, 0);
				glEnd();
			}
		}
	}
	void drawGroundTriangles() {
		int idxColor = 0;
		for (int x=-100; x<100; x+=1) {
			for (int y=-100; y<100; y++) {
				glBegin(GL_TRIANGLES);
				idxColor++;
				glColor3f(idxColor%3==0, idxColor%3==1, idxColor%3==2);
				glVertex3f(x-0.5, y-0.5, 0);
				idxColor++;
				glColor3f(idxColor%3==0, idxColor%3==1, idxColor%3==2);
				glVertex3f(x-0.5, y+0.5, 0);
				idxColor++;
				glColor3f(idxColor%3==0, idxColor%3==1, idxColor%3==2);
				glVertex3f(x+0.5, y+0.5, 0);


				glColor3f(1, 1, 1);
				glVertex3f(x-0.5, y-0.5, 0);
				glVertex3f(x+0.5, y-0.5, 0);
				glVertex3f(x+0.5, y+0.5, 0);
				glEnd();
			}
		}
	}

	void drawObjects() {
		int idxColor = 0;
		for (int x=-50; x<50; x+=7) {
			for (int y=-50; y<50; y+=7) {
				glColor3f(idxColor%3==0, idxColor%3==1, idxColor%3==2);

				if (idxColor%2==0) drawModelLines(&pyramid, point3(x, y, 0));
				else drawModelLines(&cone1, point3(x, y, 0));

				idxColor++;
			}
		}

		int x_min = -50; 
		int x_max = 50;
		int y_min = -50;
		int y_max = 50;
		int step = 5;
		glColor3f(0., 1., 0.);
		for (int x=x_min; x<=x_max; x+=step) {
			for (int y=y_min; y<=y_max; y+=step) {
				Point3 P = point3(x, y, 3);
				drawModelLines(&pyramid, P);
			}
		}

	}
	void drawGroundLines() {
		glColor3f(1., 1., 1.);
		glBegin(GL_LINES);	
		//////////////////////////////////
		for (int i=0; i<=100; i++) {
			// đường dọc
			glVertex3f(i, 0, 0);
			glVertex3f(i, 100, 0);

			// đường ngang
			glVertex3f(0, i, 0);
			glVertex3f(100, i, 0);
		}

		//for (int i=0; i<100; i++) {
		//	for (int j=0; j<100; j++) {
		//		glVertex3f(i, j, 0);
		//		glVertex3f(i, j+1, 0);
		//
		//		glVertex3f(i, j+1, 0);
		//		glVertex3f(i+1, j+1, 0);
		//
		//		glVertex3f(i+1, j+1, 0);
		//		glVertex3f(i+1, j, 0);
		//
		//		glVertex3f(i+1, j, 0);
		//		glVertex3f(i, j, 0);
		//	}
		//}

		//////////////////////////////////
		glEnd();
	}
	void display(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		gluLookAt(x, y, 1.0f,
			x+lx, y+ly, 1.0f,
			0.0f, 0.0f, 1.0f);

		drawGroundLines();
		//drawGround();
		//drawGroundQuads1();
		//drawGroundQuads();
		//drawGroundTriangles();

		//glColor3f(0., 1., 0.);//RGB
		//drawModelLines(&pyramid);
		//drawModelLines(&cone1);

		drawObjects();

		//glutSwapBuffers();
		glFlush();
	}

	void processNormalKeys(unsigned char key, int x, int y) {

		//if (key == 27)
		//	exit(0);
	}

	void processSpecialKeys(int key, int xx, int yy) {

		float fraction = 0.1f; // bước di chuyển k
		float beta = 0.01f;

		switch (key) {
		case GLUT_KEY_LEFT:
			angle += beta;
			lx = cos(angle);
			ly = sin(angle);
			break;
		case GLUT_KEY_RIGHT:
			angle -= beta;
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
	}
};
int vidu7(int argc, char **argv) {

	// init GLUT and create window

	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitDisplayMode(GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("opengl");
	vd7::init();
	// register callbacks
	glutDisplayFunc(vd7::display);
	glutReshapeFunc(vd7::changeSize);
	glutIdleFunc(vd7::display);
	glutKeyboardFunc(vd7::processNormalKeys);
	glutSpecialFunc(vd7::processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

