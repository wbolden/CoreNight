#include "Input.h"
#include <iostream>

#include "BoundingBox.h"

	double mouseX;
	double mouseY;
	bool mclicked;

	float moveX;
	float moveY;

	
float Input::getX()
{
	return moveX;
}
float Input::getY()
{
	return moveY;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
	{
#ifdef DEBUG
		std::cout << key << std::endl;
#endif
		if(key == GLFW_KEY_W)
		{
			moveY = -0.01f;
		}

		if(key == GLFW_KEY_S)
		{
			moveY = 0.01f;
		}

		if(key == GLFW_KEY_A)
		{
			moveX = 0.01f;
		}

		if(key == GLFW_KEY_D)
		{
			moveX = -0.01f;
		}
	}

	if(action == GLFW_RELEASE)
	{
#ifdef DEBUG
		std::cout << key << std::endl;
#endif

		if(key == GLFW_KEY_W)
		{
			moveY = 0.00f;
		}

		if(key == GLFW_KEY_S)
		{
			moveY = -0.00f;
		}

		if(key == GLFW_KEY_A)
		{
			moveX = -0.00f;
		}

		if(key == GLFW_KEY_D)
		{
			moveX = 0.00f;
		}
	}
}

static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{


#ifdef DEBUG
	std::cout << "x" << xpos << std::endl;
	std::cout << "y" << ypos << std::endl;
#endif

	mouseX = xpos;
	mouseY = ypos;

}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	//clicked = false;
	//std::cout << "noclick" << std::endl;
	if(action == GLFW_PRESS)
	{
#ifdef DEBUG
		std::cout << "Mouse button input" << std::endl;
#endif


		mclicked = true;
	}
}

bool Input::clicked()
{
	return mclicked;
}

void Input::resetClickedState()
{
	mclicked = false;
	//moveX = 0;
	//moveY = 0;
}

Input::Input(void)
{
	mclicked = false;
	mouseX = 0;
	mouseY = 0;
	moveX = 0;
	moveY = 0;
}

Input::Input(GLFWwindow* window)
{
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	/*
	unsigned char pixels[16 * 16 * 4];
memset(pixels, 0xff, sizeof(pixels));
GLFWimage image;
image.width = 16;
image.height = 16;
image.pixels = pixels;
GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
*/


}

double Input::getMouseX()
{
	return mouseX;
}

double Input::getMouseY()
{
	return mouseY;
}

Input::~Input(void)
{
}
