#include <windows.h>
#include <math.h>
#include <vector>
#include "glut.h"

#include "../MathExpr/mathTree.h"
#define toRad 2.0 * 3.14159 / 360.0 *

using namespace std;

mathTree expr;

bool keyDown()
{
	for (int i(0); i < 255; i++)
		if (GetAsyncKeyState(i) < 0)
			return true;
	return false;
}

void line(float x, float y, float d, float a)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(x + d * cos(toRad a), y + d * sin(toRad a));
	glVertex2f(x - d * cos(toRad a), y - d * sin(toRad a));
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	line(0, 0, 9, 0);
	line(0, 0, 9, 90);
	for (int i = -9; i <= 9; i++)
	{
		line(i, 0, 0.5, 90);
		line(0, i, 0.5, 0);
	}
	
	vector<pair<float,float>> func;
	for(float i=-9.0;i<=9;i+=0.1)
	{
		func.push_back(pair<float,float>(i,expr.calc({i})));
	}


	glutSwapBuffers();
	while (true)
	{
		if (keyDown())
			exit(0);
	}
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("plot");
	glutDisplayFunc(display);

	cout << "y = ";
	string e;
	cin >> e;
	expr.set(e);

	init();
	glutMainLoop();
}