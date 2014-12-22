#pragma once

#include <GLFW/glfw3.h>
#include "BoundingBox.h"
#include "Story.h"
#include <vector>
#include <string>

/*
	Handles loading and formatting of text to be displayed by Display
*/
class Text
{
public:
	Text(void);

	int getNumTextVerts();

	int getNumBoxVerts();

	//Generates BoundingBox and VAO for text
	//void genText(std::string text, float y, int screenWidth, int screenHeight, float scale, bool showBB);
	void genText(std::string text, float y, float xBeginf, float xEndf, int screenWidth, int screenHeight, float scale, bool showBB, bool noPred);
	//Generates BoundingBox and VAO for text
	void genText(std::vector<Dialogue> text, float yStatement, float yResponses, int screenWidth, int screenHeight, float scale, bool showStatementBB, bool showResponseBB);

	//Returns a vector of BoundingBoxes. BoundingBoxes are storied in the order of the vector of Dialogue
	std::vector<BoundingBox> getBoundingBox();

	int contains(double x, double y);

	GLuint getTextVAO();
	GLuint getBoxVAO();

	bool showBox();
	void reset();


	~Text(void);

private:
	void genBox();
	GLuint boxVAO;
	GLuint boxVertVBO;
	GLuint boxIdVBO;
	int numBoxVerts;
	std::vector<BoundingBox> boxes;


	int numTextVerts;
	GLuint textVAO;
	GLuint textVertVBO;
	GLuint textTexVBO;

	bool showb;

};

