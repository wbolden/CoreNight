#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Input
{
public:
	Input(void);
	Input(GLFWwindow* window);

	double getMouseX();
	double getMouseY();

	float getX();
	float getY();

	bool clicked();

	void resetClickedState();

	~Input(void);

private:


};

