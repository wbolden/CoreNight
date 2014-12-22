#include "Display.h"
#include <fstream>
#include <iostream>

Display::Display()
{

}

GLuint tex = 0;
GLuint t2 = 0;

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "Text.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
	
//Text text;

Display::Display(GLFWwindow* window)
{
	pause = false;
	clear = false;

	camPos = glm::vec3(0.0f, 1.0f, -5.0f);

	/*
	tex = loadTexure("font/font.png");
	t2 = loadTexure("images/tst.png");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, t2);

	*/
	//guiShaders = initShaders("shaders/panel.glsl", "shaders/frag.glsl");


	/*
	
	int w, h, comp;
	unsigned char* image = stbi_load("font/font.png", &w, &h, &comp, STBI_rgb_alpha);

	//Flip

	int wbyte = w*4;
	unsigned char *top = NULL;
	unsigned char* bottom = NULL;
	unsigned char temp = 0;
	int hh = h/2;

	for(int r = 0; r < hh; r++)
	{
		top = image + r * wbyte;
		bottom = image + (h - r - 1) * wbyte;
		for(int col = 0; col < wbyte; col++)
		{
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}


	//flip
	

	glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



	//int w, h, comp;
	unsigned char* image2 = stbi_load("images/tst.png", &w, &h, &comp, STBI_rgb_alpha);

	//Flip

	 wbyte = w*4;
	 *top = NULL;
	 bottom = NULL;
temp = 0;
	 hh = h/2;

	for(int r = 0; r < hh; r++)
	{
		top = image2 + r * wbyte;
		bottom = image2 + (h - r - 1) * wbyte;
		for(int col = 0; col < wbyte; col++)
		{
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}


	//flip
	

	glGenTextures(1, &t2);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, t2);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, t2);

//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, tex);


//	glBindTexture(GL_TEXTURE_2D, 0);


//	glBindTexture(GL_TEXTURE_2D, 0);
	
	//glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	*/
}

GLuint Display::loadTexure(const char* texturePath)
{
	GLuint texture;

	int w, h, comp;
	unsigned char* image = stbi_load(texturePath, &w, &h, &comp, STBI_rgb_alpha);

	//Flip
	int wbyte = w*4;
	unsigned char *top = NULL;
	unsigned char* bottom = NULL;
	unsigned char temp = 0;
	int hh = h/2;

	for(int r = 0; r < hh; r++)
	{
		top = image + r * wbyte;
		bottom = image + (h - r - 1) * wbyte;
		for(int col = 0; col < wbyte; col++)
		{
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}
	//flip
	
	glGenTextures(1, &texture);
//	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	free(image);

	return texture;
}




const char* loadShader(const char* filename)
{
	std::ifstream file;
	file.open(filename);

	std::string shader = "";

	while(!file.eof())
	{
		std::string temp;
		std::getline(file, temp);
		shader += temp;
		shader += '\n';
	}

	int length = shader.length();

	char* data = new char[shader.length()+1];
	memcpy(data, shader.c_str(), shader.length()*sizeof(char));
	data[shader.length()] = '\0';

	return data;
}

bool shaderCompiled(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	return (bool) status;
}

bool compileShader(GLuint shader, const GLchar* shaderSource)
{
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	return shaderCompiled(shader);
}

GLuint Display::initShaders(const char* vshaderPath, const char* fshaderPath)
{
	//const char* vshader = loadShader("vert.glsl");
	const char* vshader = loadShader(vshaderPath);
	const char* fshader = loadShader(fshaderPath);


	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);



	if(!compileShader(vs, (const GLchar*)vshader))
	{
		std::cout << "Failed to load Vertex Shader from " << vshaderPath << std::endl;

		GLchar* info = new GLchar[10000];
		glGetShaderInfoLog(vs, 10000, NULL, info);
		printf("%s\n", info);
		delete[] info;
	}
	else
	{
		std::cout << "Vertex Shader loaded from " << vshaderPath << std::endl;
	}

	if(!compileShader(fs, (const GLchar*)fshader))
	{
		std::cout << "Failed to load Fragment Shader " << fshaderPath << std::endl;

		GLchar* info = new GLchar[10000];
		glGetShaderInfoLog(fs, 10000, NULL, info);
		printf("%s\n", info);
		delete[] info;
	}
	else
	{
		std::cout << "Fragment Shader loaded from " << fshaderPath << std::endl;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fs);
	glAttachShader(shaderProgram, vs);
	glLinkProgram(shaderProgram);

	return shaderProgram;
}

/*
void Display::render(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 0.5);
	int texloc = glGetUniformLocation(guiShaders, "tex");
	glUseProgram(guiShaders);
	glUniform1i(texloc, 1);

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glfwSwapBuffers(window);
}

void Display::render(GLFWwindow* window, GLuint tvao, int numVerts)
{
	int texloc = glGetUniformLocation(guiShaders, "tex");
	glUniform1i(texloc, 1);
	glUseProgram(guiShaders);
	

	glBindVertexArray(tvao);

	glDrawArrays(GL_TRIANGLES, 0, numVerts);
}
*/

void Display::render(GLuint vao, int numVerts, int shaderProgram)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, numVerts);
}

void Display::renderText(Text& text, float* sColor, float* rColor, int active, GLuint guiShader, GLuint textShader, GLuint texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
//	std::cout << active << std::endl;
	//text.showBox
	if(active != -2)
	{
		int guiuloc = glGetUniformLocation(guiShader, "active");
		glUseProgram(guiShader);
		glUniform1i(guiuloc, active);
		glBindVertexArray(text.getBoxVAO());
		glDrawArrays(GL_TRIANGLES, 0, text.getNumBoxVerts());

//#ifdef DEBUG
//		std::cout << active << std::endl;
//#endif
	}

	glUseProgram(textShader);
	glBindVertexArray(text.getTextVAO());
	glDrawArrays(GL_TRIANGLES, 0, text.getNumTextVerts());
}

void renderCharacter();

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

void Display::renderScene(Scene& scene, GLuint sceneShader)
{
	if(scene.usesTexture())
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, scene.getTexture());
		int posloc = glGetUniformLocation(sceneShader, "pos");

		glUseProgram(sceneShader);

		//glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(scene.pos[0], scene.pos[1], 0.0f));

		glUniform2f(posloc, scene.pos[0], scene.pos[1]);
		//glUniformMatrix4fv(matloc, 1, GL_FALSE, glm::value_ptr(trans));

		int matloc = glGetUniformLocation(sceneShader, "scale");

		glm::mat4 scale = glm::scale(glm::vec3(scene.scale, scene.scale, scene.scale));

		glUniformMatrix4fv(matloc, 1, GL_FALSE, glm::value_ptr(scale));

		glBindVertexArray(scene.getVAO());

		
		glDrawArrays(GL_TRIANGLES, 0, scene.getNumVerts());
	}
	else
	{
		//setting color uniforms
	}
//	glBindTexture(

	
	//glBindVertexArray(
}

void Display::renderButton(GLuint bvao, int numVerts, GLuint buttonShader, float* color)
{
		int guiuloc = glGetUniformLocation(buttonShader, "color");
		glUseProgram(buttonShader);
		glUniform4f(guiuloc, color[0], color[1], color[2], color[3]);
		glBindVertexArray(bvao);
		glDrawArrays(GL_TRIANGLES, 0, numVerts);

		//std::cout << active << std::endl;
}

void Display::renderFadeScene(Scene& scene1, Scene& scene2, GLuint fadeShader, float fade, float focus)
{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, scene1.getTexture());

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, scene2.getTexture());

		int fadeloc = glGetUniformLocation(fadeShader, "fade");
		int focusloc = glGetUniformLocation(fadeShader, "focus");
		//glUseProgram(guiuloc);
		glUseProgram(fadeShader);

		glUniform1f(fadeloc, fade);
		glUniform1f(focusloc, focus);

		
		glBindVertexArray(scene1.getVAO());

		
		glDrawArrays(GL_TRIANGLES, 0, scene1.getNumVerts());
}

//make struct for color?
void renderGUI(GLuint vao, int numVerts, float* color, int active, GLuint guiShader)
{

}

bool Display::paused()
{
	return pause;
}

Display::~Display()
{
//	glfwDestroyWindow(window);
//	glfwTerminate();
}