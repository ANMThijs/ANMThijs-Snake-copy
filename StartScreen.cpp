#include "StartScreen.h"

void DrawMainMenu() {
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);

	//Render the green button
	glColor3f(0.2f, 0.8f, 0.2f);

	glVertex2f(-50.0f, 50.0f);
	glVertex2f(-150.0f, 50.0f);
	glVertex2f(-150.0f, -50.0f);

	glVertex2f(-50.0f, 50.0f);
	glVertex2f(-150.0f, -50.0f);
	glVertex2f(-50.0f, -50.0f);

	//Render the red button
	glColor3f(0.8f, 0.2f, 0.2f);

	glVertex2f(50.0f, 50.0f);
	glVertex2f(150.0f, 50.0f);
	glVertex2f(150.0f, -50.0f);

	glVertex2f(50.0f, 50.0f);
	glVertex2f(150.0f, -50.0f);
	glVertex2f(50.0f, -50.0f);

	glEnd();
}