#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265f

int w = 500, h = 500;

GLfloat ballRadius = 0.1f;

void Start(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(w/2, w/2, h/2, h/2);
	glMatrixMode(GL_MODELVIEW);
}

void display(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		int numSegments = 100;
		GLfloat angle;
		for (int i = 0; i <= numSegments; i++) {
			angle = i * 2.0f * PI / numSegments;
			glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
		}
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Click on the button");
	glutDisplayFunc(display);
	
	Start();
	glutMainLoop();
}
