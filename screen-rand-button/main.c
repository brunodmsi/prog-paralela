#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <GL/glut.h>

#define THREAD_NUM 4
#define RESOLUTION 500.0f
#define RANDOM_MAX 500

GLfloat win;
int timerCounter = 0, 
		currBuff = 0, 
		buttonClickCounter = 0, 
		missedClickCounter = 0;

int redrawRate = 1000;
double reducer = 0.90;

GLfloat x, y;
void drawSquare(int x, int y, double sidelength)
{
    double halfside = sidelength / 2;

    glColor3d(1, 0, 0);
    glBegin(GL_POLYGON);

    glVertex2d(x + halfside, y + halfside);
    glVertex2d(x + halfside, y - halfside);
    glVertex2d(x - halfside, y - halfside);
    glVertex2d(x - halfside, y + halfside);

    glEnd();
}

void keyboard(int key, int x, int y) {
	switch(key) {
		case 27:
			exit(0);
			break;
	}
}

void mouse(int button, int state, int x, int y) {
	float pixel[3];
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		glReadPixels(x, 500 - 1 - y, 1, 1, GL_RGB, GL_FLOAT, &pixel);
		// printf("%f %f %f \n", pixel[0], pixel[1], pixel[2]);
		if ((int) pixel[0] == 1) {
			redrawRate = redrawRate * reducer;
			buttonClickCounter++;
		} else missedClickCounter++;
	}
}

int randomInRange(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void drawOnScreen(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	drawSquare(x, y, 30);

	glutSwapBuffers();
}

void redraw(void) {
	if (timerCounter > currBuff) {
		currBuff = timerCounter;

		x = (GLfloat) randomInRange(-RANDOM_MAX, RANDOM_MAX);
		y = (GLfloat) randomInRange(-RANDOM_MAX, RANDOM_MAX);

		glutPostRedisplay();	
	}
}

void timer(int extra) {
	timerCounter += redrawRate;

	if (timerCounter / 1000 >= 60) {
		printf("\nResultados:\nClicks certos: %d\nClicks errados: %d\n", 
			buttonClickCounter,
			missedClickCounter
		);

		float rateInMs = (float) redrawRate / 1000;
		printf("A taxa de redução/click é de %.2f%%,\no redesenho foi de 1 segundo para: %.3fms\n\n", 
			1 - reducer, 
			rateInMs
		);

		exit(0);
	}

	glutTimerFunc(redrawRate, timer, 0);
}

void start(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	win = RESOLUTION;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-win, win, -win, win);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(RESOLUTION, RESOLUTION);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Desenhador de Linha");
	glutDisplayFunc(drawOnScreen);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(redraw);
	glutTimerFunc(redrawRate, timer, 0);
	start();
	glutMainLoop();
}
