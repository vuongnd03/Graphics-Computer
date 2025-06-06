//
// Ky thuat do hoa
// Ha Manh Toan hmtoan@ioit.ac.vn
//
#include <glut.h>
#include <stdio.h>
#include "imageloader.h"

#include <time.h>
namespace vd9 {
	float rx=0, ry=0, rz=1, angle=0; 
	GLuint texture=0;
	//double thoigiantruoc;
	void init() {
		texture = textureFromBMP("data/c.bmp");

		//thoigiantruoc = time(NULL)/1000;
	}
	void release() {
		glDeleteTextures(1, &texture);
	}

	void draw() {

		glBindTexture(GL_TEXTURE_2D, texture);
		
		glPushMatrix();
		glRotatef(angle, rx, ry, rz);
		glBegin(GL_TRIANGLES);
#if 0
		glTexCoord2f(0.0, 1.0);  glVertex3f(0, 0, 2);
		glTexCoord2f(1.0, 1.0);  glVertex3f(-1, -1, 0);
		glTexCoord2f(1.0, 0.0);  glVertex3f(-1, 1, 0);

		glTexCoord2f(0.0, 1.0);  glVertex3f(0, 0, 2);
		glTexCoord2f(0.0, 0.0);  glVertex3f(-1, 1, 0);
		glTexCoord2f(1.0, 0.0);  glVertex3f(1, 1, 0);

		glTexCoord2f(0.0, 1.0);  glVertex3f(0, 0, 2);
		glTexCoord2f(1.0, 1.0);  glVertex3f(1, 1, 0);
		glTexCoord2f(1.0, 0.0);  glVertex3f(1, -1, 0);

		glTexCoord2f(0.0, 1.0);  glVertex3f(0, 0, 2);
		glTexCoord2f(0.0, 0.0);  glVertex3f(1, -1, 0);
		glTexCoord2f(1.0, 0.0);  glVertex3f(-1, -1, 0);
#else

		glColor3f(0.0, 1.0, 0.0);  glVertex3f(0, 0, 2);
		glColor3f(1.0, 0.0, 0.0);  glVertex3f(-1, -1, 0);
		glColor3f(0.0, 0.0, 1.0);  glVertex3f(-1, 1, 0);

		glColor3f(1.0, 0.0, 0.0);  glVertex3f(0, 0, 2);
		glColor3f(0.0, 1.0, 0.0);  glVertex3f(-1, 1, 0);
		glColor3f(1.0, 1.0, 1.0);  glVertex3f(1, 1, 0);

		glColor3f(0.0, 1.0, 1.0);  glVertex3f(0, 0, 2);
		glColor3f(1.0, 0.0, 1.0);  glVertex3f(1, 1, 0);
		glColor3f(1.0, 1.0, 0.0);  glVertex3f(1, -1, 0);

		glColor3f(0.5, 1.0, 0.0);  glVertex3f(0, 0, 2);
		glColor3f(0.5, 0.0, 5.0);  glVertex3f(1, -1, 0);
		glColor3f(0.0, 1.0, 5.0);  glVertex3f(-1, -1, 0);
#endif
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);  glVertex3f(-1, 1, 0);
		glTexCoord2f(1.0, 1.0);  glVertex3f(-1, -1, 0);
		glTexCoord2f(1.0, 0.0);  glVertex3f(1, -1, 0);
		glTexCoord2f(0.0, 0.0);  glVertex3f(1, 1, 0);
		glEnd();
		
		glPopMatrix();

		angle += 0.01;

		//thoigiantruoc = thoigianhientai;
	}

	void resize(int width, int height) {
		if (height== 0) height = 1;
		const float ar = (float)width / (float)height;
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
		gluPerspective(45.0f, ar, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(5, 5, 5, 0, 0, 1, 0, 0, 1);
		glEnable(GL_TEXTURE_2D);
	}

	void display1() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		draw();
		

		//glutSwapBuffers();
		glFlush();
	}
	void processKeys(unsigned char key, int x, int y) {
		switch (key) {
		case 'w':
			rx += 0.1;
			break;
		case 's':
			rx -= 0.1;
			break;
		case 'a':
			ry -= 0.1;
			break;
		case 'd':
			ry += 0.1;
			break;
		case 'q':
			rz -= 0.1;
			break;
		case 'e':
			rz += 0.1;
			break;
		default:
			break;
		}
		//glutPostRedisplay();
	}
};
int vidu9(int argc, char** argv) {
	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("rectangle");
	glEnable(GL_DEPTH_TEST);

	glutReshapeFunc(vd9::resize);
	glutDisplayFunc(vd9::display1);
	glutKeyboardFunc(vd9::processKeys);
	glutIdleFunc(vd9::display1);
	vd9::init();
	glutMainLoop();
	vd9::release();
	return 0;
}