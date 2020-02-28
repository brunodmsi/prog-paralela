#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265f

float w = 500.0f, h = 500.0f;

GLfloat ballRadius = 0.05f;

void Start(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(w, w, h, h);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
	float pixel[4];
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &pixel);
		printf("%f %f %f %f\n", pixel[0], pixel[1], pixel[2], pixel[3]);
	}
}

void display(void) {
	float x = 200.0f, y = 5.0f;;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		int numSegments = 100;
		GLfloat angle;
		for (int i = 0; i <= numSegments; i++) {
			angle = i * 2.0f * PI / numSegments;
			//printf("%f\n", (GLfloat) angle);
			
			float x2 = x + sin(angle) * ballRadius;
		      	float y2 = y + cos(angle) * ballRadius;	
			
			glVertex2f(x2, y2);
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
	glutMouseFunc(mouse);	
	Start();
	glutMainLoop();
}
