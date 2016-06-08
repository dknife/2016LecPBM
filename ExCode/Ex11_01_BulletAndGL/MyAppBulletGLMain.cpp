// GL Code
#include "MyBulletWorld.h"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

CBulletWorld myWorld;

void drawAxes() {
	glBegin(GL_LINES);
	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0); // x
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0); // y
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,1); // z
	glEnd();
}

void drawPlane(void) {
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINES);
	for(int i=0;i<40;i++) {
		glVertex3f(-20, 0, i-20);
		glVertex3f( 20, 0, i-20);
	}
	for(int i=0;i<40;i++) {
		glVertex3f(i-20, 0, -20);
		glVertex3f(i-20, 0,  20);
	}
	glEnd();

	glColor3f(0,0,0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(-20, 0,  0);
	glVertex3f( 20, 0,  0);
	glVertex3f(  0, 0,-20);
	glVertex3f(  0, 0, 20);
	glEnd();

}




void myDisplay() {
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 0.1, 100); //-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
	
	static float angle = 0.0;
	angle += 0.01;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(20.0, 20, 20.0, 0,0,0, 0,1,0);

	glLineWidth(1);
	drawPlane();

	glLineWidth(3);
	drawAxes();

	myWorld.step(1.0/60.0);
	myWorld.draw();
	
   
	glutSwapBuffers();
}

void myKeyboard(unsigned char k, int x, int y) {
	switch(k) {
	case 'f': myWorld.moveBall(); break;
	
	}
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Transform");

	myWorld.initialize();

	glEnable(GL_DEPTH_TEST);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
    glutMainLoop();

    return 0;
}