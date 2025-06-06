//
// Ky thuat do hoa
// Ha Manh Toan hmtoan@ioit.ac.vn
//
#include <glut.h>
#include <stdio.h>
namespace vd3 {
	const int N_POINTS = 26;
	double shape[N_POINTS][3] ={
		{ -0.8, 0.3, 0.0 },
		{ -0.8, 0.7, 0.0 },
		{ -0.9, 0.7, 0.0 },
		{ -0.7, 0.7, 0.0 },
		{ -0.6, 0.7, 0.0 },
		{ -0.4, 0.7, 0.0 },
		{ -0.4, 0.7, 0.0 },
		{ -0.4, 0.3, 0.0 },
		{ -0.4, 0.3, 0.0 },
		{ -0.6, 0.3, 0.0 },
		{ -0.6, 0.3, 0.0 },
		{ -0.6, 0.7, 0.0 },
		{ -0.3, 0.3, 0.0 },
		{ -0.2, 0.7, 0.0 },
		{ -0.2, 0.7, 0.0 },
		{ -0.1, 0.3, 0.0 },
		{ -0.25, 0.5, 0.0 },
		{ -0.15, 0.5, 0.0 },
		{ 0.0, 0.3, 0.0 },
		{ 0.0, 0.7, 0.0 },
		{ 0.0, 0.7, 0.0 },
		{ 0.2, 0.3, 0.0 },
		{ 0.2, 0.3, 0.0 },
		{ 0.2, 0.7, 0.0 },
		{ -0.25, 0.85, 0.0 },
		{ -0.15, 0.8, 0.0 }
	};
	double tx=0, ty=0;
	double angle =0;
	
	const int N_COLORS = 7;
	bool bAuto = false;
	double colors[N_COLORS][3] ={
		{ 1.0, 1.0, 1.0 },
		{ 0.0, 0.0, 1.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 }
	};
	int colorId = 0;
	int state= 0;
	void display1() {
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glColor3f(colors[colorId][0], colors[colorId][1], colors[colorId][2]);

		//glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glBegin(GL_LINES);
		for (int i=0; i<N_POINTS/2; i++) {
			glVertex3f(shape[i*2][0]+tx, shape[i*2][1]+ty, shape[i*2][2]);
			glVertex3f(shape[i*2+1][0]+tx, shape[i*2+1][1]+ty, shape[i*2+1][2]);
		}
		glEnd();
		glPopMatrix();
		
		if (bAuto) {
			//angle += 0.1;
			double s=0.0003;
			// duong thang song song truc Ox
			//if (state==0) {
			//	tx += s;
			//	if (tx>0.5) {
			//		state=1;
			//	}
			//} else {
			//	tx -= s;
			//	if (tx<-0.5) {
			//		state=0;
			//	}
			//}

			// hinh chu nhat
			if (state==0) {
				tx += s;
				if (tx>0.5) {
					state=1;
				}
			}else if (state==1) {
				ty += s;
				if (ty>0.5) {
					state=2;
				}
			} else if(state==2) {
				tx -= s;
				if (tx<-0.5) {
					state=3;
				}
			} else {
				ty -= s;
				if (ty<-0.5) {
					state=0;
				}
			}
		}

		//glutSwapBuffers();
		glFlush();
	}
	void processKeys(unsigned char key, int x, int y) {
		switch (key) {
		case 'w':
			ty += 0.1;
			break;
		case 's':
			ty -= 0.1;
			break;
		case 'a':
			tx -= 0.1;
			break;
		case 'd':
			tx += 0.1;
			break;
		case '>':
			angle -= 0.4;
			break;
		case '<':
			angle += 0.4;
			break;
		case 'p':
			bAuto = !bAuto;
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}
	void processMouse(int button, int state, int x, int y) {
		if (button==GLUT_LEFT_BUTTON && state==GLUT_UP) {
			colorId = (colorId+1)%N_COLORS;
			glutPostRedisplay();
		} 
	}
};
int vidu3(int argc, char** argv) {
	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(250, 250);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("rectangle");

	//	init();
	glutDisplayFunc(vd3::display1);
	glutKeyboardFunc(vd3::processKeys);
	glutMouseFunc(vd3::processMouse);
	glutIdleFunc(vd3::display1);
	glutMainLoop();
	return 0;
}
