#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <GL/glut.h>

#define THREAD_NUM 4
#define RESOLUTION 500.0f
#define RANDOM_MAX 500

GLfloat win;
int timer_counter = 0, currBuff = 0;

int redraw_rate = 1000;

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
	float pixel[4];
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &pixel);
		printf("%f %f %f %f\n", pixel[0], pixel[1], pixel[2], pixel[3]);
	}
}

int randomInRange(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

// void counter() {
// 	int oldSecond = 0;
// 	time_t begin;
// 	double time_spent;

// 	begin = clock();
// 	for (int i = 0; 1; i++) {
// 		time_spent = (double) (clock() - begin) / CLOCKS_PER_SEC;
		
// 		if ((int) time_spent > oldSecond) {
// 			int randX = randomInRange(-RANDOM_MAX, RANDOM_MAX);
// 			int randY = randomInRange(-RANDOM_MAX, RANDOM_MAX);
// 			drawSquare(randX, randY, 30);
// 			glutPostRedisplay();
// 		}

// 		if (time_spent >= 2.0)
// 			exit(0);

// 		oldSecond = (int) time_spent;

// 		sleep(1);
// 	}
// }

void drawOnScreen(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	drawSquare(x, y, 30);

	glFlush();
	glutSwapBuffers();
}

void redraw(void) {
	if (timer_counter > currBuff) {
		currBuff = timer_counter;

		x = (GLfloat) randomInRange(-RANDOM_MAX, RANDOM_MAX);
		y = (GLfloat) randomInRange(-RANDOM_MAX, RANDOM_MAX);
		
		glutPostRedisplay();	
	}

}

void timer(int extra) {
	timer_counter++;

	if (timer_counter >= 60) exit(0);

	glutTimerFunc(redraw_rate, timer, 0);
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
	glutTimerFunc(redraw_rate, timer, 0);
	start();
	glutMainLoop();
	// counter();
}
