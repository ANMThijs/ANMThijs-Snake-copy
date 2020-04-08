#include "Apple.h"

Apple::Apple() {

}

Apple::~Apple() {

}

void Apple::Init() {
	this->x = RandomInt(0, 19);
	this->y = RandomInt(0, 19);
}

void Apple::Init(int x, int y) {
	this->x = x;
	this->y = y;
}

void Apple::Render() {
	//create a local variable to calculate the OpenGL position
	float x = -500.0f + this->x * 50.0f;
	float y = -500.0f + this->y * 50.0f;

	glBegin(GL_TRIANGLES);

	glColor3f(AppleCol);
	glVertex2f(x + 48.0f, y + 48.0f);
	glVertex2f(x, y + 48.0f);
	glVertex2f(x, y);

	glVertex2f(x + 48.0f, y + 48.0f);
	glVertex2f(x, y);
	glVertex2f(x + 48.0f, y);

	glEnd();
}