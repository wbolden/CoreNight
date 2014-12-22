#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Text.h"



const int defaultSquareSize = 128;
const float fdim = 1.0f/16.0f;
const float globalOffset = 0.1f;

	std::string cmap = 
	"                "	//0
	"                "	//1
	" !\"#"		"$%&'"		"()*+"		",-./"	//2
	"0123"		"4567"		"89:;"		"<=>?"	//3
	"@ABC"		"DEFG"		"HIJK"		"LMNO"	//4
	"PQRS"		"TUVW"		"XYZ["		"\\]^_"	//5
	"`abc"		"defg"		"hijk"		"lmno"	//6
	"pqrs"		"tuvw"		"xyz{"		"|}~ "	//7
	;
	float offsets[] = {
		-0.03,0,0,0,					0,0,0,0,					0,0,0,0,					0,0,0,0,				//0
		0,0,0,0,						0,0,0,0,					0,0,0,0,					0,0,0,0,				//1
		0,-0.03,0,0,					0,0,0,-0.04,				0,0,0,0,					0,0,-0.04,0,			//2
		0,0,0,0,						0,0,0,0,					0,0,0,0,					0,0,0,0,				//3
		0,0.015,0.015,0.015,			0.015,0.015,0.015,0.015,	0.015,-0.035,-0.01,0.015,	0.015,0.04,0.03,0.015,	//4
		0.015,0.015,0.015,0.015,		0.015,0.015,0.015,0.045,	0.015,0.015,0.015,0,		0,0,0,0,				//5
		0,0,0,0,						0,0,-0.03, 0.00,			0,-0.04,-0.03,-0.01,		-0.04,0.04,0.01,0,		//6
		0,0,-0.02,0,					-0.02,0,0,0.03,				0.0,0,0,0,					0,0,0,0					//7
	};


Text::Text(void)
{
	textVAO = 0;
	textTexVBO = 0;
	textVertVBO = 0;
	numTextVerts = 0;
	numBoxVerts = 0;

	boxVAO = 0;
	boxVertVBO = 0;
	boxIdVBO = 0;

	//load tex?
}

int Text::getNumTextVerts()
{
	return numTextVerts;
}

int Text::getNumBoxVerts()
{
	return numBoxVerts;
}

void Text::genBox()
{
	numBoxVerts = boxes.size() * 12;
	GLfloat* vertices = new GLfloat[boxes.size() * 12];
	GLfloat* boxids = new GLfloat[boxes.size()*6];

//	for(int i = 0; i < boxes.size()*12; i++)
//	{
//		boxids[i] = (GLfloat)(i / 12);
//	}

	for(int i = 0; i < boxes.size()*6; i++)
	{
		boxids[i] = (GLfloat)(i/6);
	}

	for(int i = 0; i < boxes.size(); i++)
	{
		int arrIndex = 12*i;


		vertices[arrIndex+0] = boxes[i].fx1;		vertices[arrIndex+1] = boxes[i].fy2;
		vertices[arrIndex+2] = boxes[i].fx2;		vertices[arrIndex+3] = boxes[i].fy2;
		vertices[arrIndex+4] = boxes[i].fx1;		vertices[arrIndex+5] = boxes[i].fy1;
		vertices[arrIndex+6] = boxes[i].fx1;		vertices[arrIndex+7] = boxes[i].fy1;
		vertices[arrIndex+8] = boxes[i].fx2;		vertices[arrIndex+9] = boxes[i].fy2;
		vertices[arrIndex+10]= boxes[i].fx2;		vertices[arrIndex+11]= boxes[i].fy1;
	}


	glGenBuffers(1, &boxVertVBO);
	glBindBuffer(GL_ARRAY_BUFFER, boxVertVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*boxes.size() * 12, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &boxIdVBO);
	glBindBuffer(GL_ARRAY_BUFFER, boxIdVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*boxes.size()*6, boxids, GL_STATIC_DRAW);
	
	glGenVertexArrays(1, &boxVAO);
	glBindVertexArray(boxVAO);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, boxVertVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, boxIdVBO);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);


	delete [] vertices;
	delete [] boxids;
}

//add border factor
void Text::genText(std::string text, float y, float xBeginf, float xEndf, int screenWidth, int screenHeight, float scale, bool showBB, bool noPred)
{
	showb = showBB;
	reset();

	numTextVerts = text.length() * 12;
	GLfloat* vertices = new GLfloat[numTextVerts];
	GLfloat* texCoords = new GLfloat[numTextVerts];

	//avoid the edges
	int ledge = 50;
	int yedge = 500;

	int width = 1280;

	float scaledSquareSize = defaultSquareSize*scale;

	int squaresPerLine = (int)(width/(scaledSquareSize)) * 2;

	//squaresPerLine


	float ynorm = (1.0f -2.0f*y); //the y coordinate normalized [-1, 1]
	float dxynorm = 2*scaledSquareSize/(2.0f*720.0f); //Change in x or y normalized 
	float dxxnorm = 0; //finish

	float xStart = -dxynorm* (float)squaresPerLine/2 + xBeginf;
	float xEnd = -xStart - xEndf;

	float xCurrent = xStart;

	//Variables for BoundingBox construction
	int ix1, ix2, iy1, iy2;
	float x1, x2, y1, y2;
	x1 = xStart;
	x2 = xEnd;
	y1 = ynorm;

	//float ofsetScale = scale * (1)

	int textRow = 0;

	for(int i = 0; i < text.length(); i++)
	{
		int arrIndex = i * 12;

		/*
			Finds a characters position on the character map and maps texture coordinates
		*/

		int mapPos = cmap.find(text[i]);
		int x = (mapPos%16);
		int y = 15 - mapPos/16;

		texCoords[arrIndex+0] = x * fdim;		texCoords[arrIndex+1] = y*fdim;
		texCoords[arrIndex+2] = x*fdim + fdim;	texCoords[arrIndex+3] =  y*fdim;
		texCoords[arrIndex+4] = x*fdim;			texCoords[arrIndex+5] =  y*fdim + fdim;
		texCoords[arrIndex+6] = x*fdim;			texCoords[arrIndex+7] =  y*fdim + fdim;
		texCoords[arrIndex+8] = x*fdim + fdim;	texCoords[arrIndex+9] =  y*fdim;
		texCoords[arrIndex+10] = x*fdim + fdim;	texCoords[arrIndex+11] =  y*fdim+fdim;

		/*
			The following two if blocks handle moving to the next line (y) when out of room
		*/

		if(xCurrent + dxynorm >= xEnd)
		{
			textRow++;
			xCurrent = xStart;
		}

		//If the new word might get split, bump to next line
		if(text[i] == ' ' && !noPred)
		{
			int wordStart = i;
			while(text[wordStart] == ' ')
			{
				wordStart++;
			}

			int wordEnd = wordStart;
			while((text[wordEnd] != ' ') && (text[wordEnd] != '\0'))
			{
				wordEnd++;
			}

			if(xCurrent + (dxynorm - 0.5*globalOffset*scale) * (wordEnd - wordStart) > xEnd)
			{
				textRow++;
				xCurrent = xStart;
			}
		}

		/*
			Maps the vertices with offsets to improve the look of the text
		*/

		float ofs = offsets[mapPos]*scale;
		float mofs = ofs *0.5f; //Middle offset

		float newXCurrent = xCurrent + dxynorm + ofs - globalOffset*scale;

		//Avoids weird hanging spaces at the start of lines
		if(text[i] == ' ' && (xCurrent == xStart))
		{
			newXCurrent = xStart;
		}
		
		vertices[arrIndex+0] = xCurrent + mofs;					vertices[arrIndex+1] = ynorm - (textRow+1)*dxynorm;
		vertices[arrIndex+2] = xCurrent +dxynorm + mofs;		vertices[arrIndex+3] = ynorm - (textRow+1)*dxynorm;
		vertices[arrIndex+4] = xCurrent + mofs;					vertices[arrIndex+5] = ynorm - textRow*dxynorm;
		vertices[arrIndex+6] = xCurrent + mofs;					vertices[arrIndex+7] = ynorm - textRow*dxynorm;
		vertices[arrIndex+8] = xCurrent +dxynorm + mofs;		vertices[arrIndex+9] = ynorm - (textRow+1)*dxynorm;
		vertices[arrIndex+10]= xCurrent +dxynorm + mofs;		vertices[arrIndex+11]= ynorm - textRow*dxynorm;

		xCurrent = newXCurrent;
	}

	/*
		Constructs the bounding box with relevant information and pushes it on the boxes vector
	*/

	y2 = ynorm - (textRow+1)*dxynorm;

	float halfWidth = screenWidth/2.0f;
	float halfHeight = screenHeight/2.0f;

	ix1 = (x1*(screenHeight/(float)screenWidth)+1) * halfWidth;
	ix2 = (x2*(screenHeight/(float)screenWidth)+1) * halfWidth;
	iy1 = screenHeight - (y1+1.0f) * halfHeight;
	iy2 = screenHeight - (y2+1.0f) * halfHeight;

	BoundingBox b(ix1, iy1, ix2, iy2);
	b.setUPos(x1, y1, x2, y2);
	boxes.push_back(b);



	//Bind
	glGenBuffers(1, &textVertVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textVertVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numTextVerts, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &textTexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textTexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numTextVerts, texCoords, GL_STATIC_DRAW);

	glGenVertexArrays(1, &textVAO);
	glBindVertexArray(textVAO);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, textVertVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, textTexVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	

	delete [] vertices;
	delete [] texCoords;

	genBox();
}

bool Text::showBox()
{
	return showb;
}

void Text::genText(std::vector<Dialogue> text, float yStatement, float yResponses, int screenWidth, int screenHeight, float scale, bool showStatementBB, bool showResponseBB)
{
	reset();
	//Same as other gen text but generates multiple bounding boxes/polygons to present them and sections of text for each Dialogue in the vector.
	numTextVerts = 0; 

	for(int i = 0; i < text.size(); i++) //Space for the dialogue
	{
		numTextVerts += 12*text[i].dialogue.length();
	}

	GLfloat* vertices = new GLfloat[numTextVerts];
	GLfloat* texCoords = new GLfloat[numTextVerts];

	//avoid the edges
	int width = 1280 - 100;

	float scaledSquareSize = defaultSquareSize*scale;

	int squaresPerLine = (int)(width/(scaledSquareSize)) * 2;



	float ynormStatement = 1.0f - 2.0f*yStatement; //the y coordinate normalized [-1, 1]
	float ynormResponses = 1.0f - 2.0f*yResponses; //the y coordinate normalized [-1, 1]

	float dxynorm = 2*scaledSquareSize/(2.0f*720.0f); //Change in x or y normalized 
	float dxxnorm = 0; //finish

	float xStart = -dxynorm* (float)squaresPerLine/2;
	float xEnd = -xStart;

	float xCurrent = xStart;
	int textRow = 0;

	int ix1, ix2, iy1, iy2;
	float x1, x2, y1, y2;

	///////////////////////////////////////////////// THIS IS FOR THE STATEMENT ///////////////////////////////////////


	x1 = xStart;
	x2 = xEnd;
	y1 = ynormStatement;

//	int textRow = 0;

	int arrIndex = 0;

	for(int i = 0; i < text[0].dialogue.length(); i++)
	{
		arrIndex = i * 12;

		/*
			Finds a characters position on the character map and maps texture coordinates
		*/

		int mapPos = cmap.find(text[0].dialogue[i]);
		int x = (mapPos%16);
		int y = 15 - mapPos/16;

		texCoords[arrIndex+0] = x * fdim;		texCoords[arrIndex+1] = y*fdim;
		texCoords[arrIndex+2] = x*fdim + fdim;	texCoords[arrIndex+3] =  y*fdim;
		texCoords[arrIndex+4] = x*fdim;			texCoords[arrIndex+5] =  y*fdim + fdim;
		texCoords[arrIndex+6] = x*fdim;			texCoords[arrIndex+7] =  y*fdim + fdim;
		texCoords[arrIndex+8] = x*fdim + fdim;	texCoords[arrIndex+9] =  y*fdim;
		texCoords[arrIndex+10] = x*fdim + fdim;	texCoords[arrIndex+11] =  y*fdim+fdim;

		/*
			The following two if blocks handle moving to the next line (y) when out of room
		*/

		if(xCurrent + dxynorm >= xEnd)
		{
			textRow++;
			xCurrent = xStart;
		}

		//If the new word might get split, bump to next line
		if(text[0].dialogue[i] == ' ')
		{
			int wordStart = i;
			while(text[0].dialogue[wordStart] == ' ')
			{
				wordStart++;
			}

			int wordEnd = wordStart;
			while((text[0].dialogue[wordEnd] != ' ') && (text[0].dialogue[wordEnd] != '\0'))
			{
				wordEnd++;
			}

			if(xCurrent + (dxynorm - 0.5*globalOffset*scale) * (wordEnd - wordStart) > xEnd)
			{
				textRow++;
				xCurrent = xStart;
			}
		}

		/*
			Maps the vertices with offsets to improve the look of the text
		*/

		float ofs = offsets[mapPos]*scale;
		float mofs = ofs *0.5f; //Middle offset
		float newXCurrent = xCurrent + dxynorm + ofs - globalOffset*scale;

		//Avoids weird hanging spaces at the start of lines
		if(text[0].dialogue[i] == ' ' && (xCurrent == xStart))
		{
			newXCurrent = xStart;
		}
		
		vertices[arrIndex+0] = xCurrent + mofs;					vertices[arrIndex+1] = ynormStatement - (textRow+1)*dxynorm;
		vertices[arrIndex+2] = xCurrent +dxynorm + mofs;		vertices[arrIndex+3] = ynormStatement - (textRow+1)*dxynorm;
		vertices[arrIndex+4] = xCurrent + mofs;					vertices[arrIndex+5] = ynormStatement - textRow*dxynorm;
		vertices[arrIndex+6] = xCurrent + mofs;					vertices[arrIndex+7] = ynormStatement - textRow*dxynorm;
		vertices[arrIndex+8] = xCurrent +dxynorm + mofs;		vertices[arrIndex+9] = ynormStatement - (textRow+1)*dxynorm;
		vertices[arrIndex+10]= xCurrent +dxynorm + mofs;		vertices[arrIndex+11]= ynormStatement - textRow*dxynorm;

		xCurrent = newXCurrent;
	}

	/*
		Constructs the bounding box with relevant information and pushes it on the boxes vector
	*/

	y2 = ynormStatement - (textRow+1)*dxynorm;

	float halfWidth = screenWidth/2.0f;
	float halfHeight = screenHeight/2.0f;

	ix1 = (x1*(screenHeight/(float)screenWidth)+1) * halfWidth;
	ix2 = (x2*(screenHeight/(float)screenWidth)+1) * halfWidth;
	iy1 = screenHeight - (y1+1) * halfHeight;
	iy2 = screenHeight - (y2+1) * halfHeight;

	BoundingBox b(ix1, iy1, ix2, iy2);
	b.setUPos(x1, y1, x2, y2);
	boxes.push_back(b);

	
	////////////////////////////////////////////////////// END OF SPECIAL CASE FOR STATEMENT //////////////////////////////////////////////////////

	arrIndex = text[0].dialogue.length() * 12 - 12;

	//ynormResponses

	//int ix1, ix2, iy1, iy2;
	//float x1, x2, y1, y2;


	textRow = -1;



	for(int vpos = 1; vpos < text.size(); vpos++)
	{
		xCurrent = xStart; //correct
		textRow++; //c

	//	x1 = xStart;
	//	x2 = xEnd;
		x1 = xStart;
		x2 = xEnd;
		y1 = ynormResponses -textRow*dxynorm;


		for(int i = 0; i < text[vpos].dialogue.length(); i++)
		{
			arrIndex += 12;

			/*
				Finds a characters position on the character map and maps texture coordinates
			*/

			int mapPos = cmap.find(text[vpos].dialogue[i]);
			int x = (mapPos%16);
			int y = 15 - mapPos/16;

			texCoords[arrIndex+0] = x * fdim;		texCoords[arrIndex+1] = y*fdim;
			texCoords[arrIndex+2] = x*fdim + fdim;	texCoords[arrIndex+3] =  y*fdim;
			texCoords[arrIndex+4] = x*fdim;			texCoords[arrIndex+5] =  y*fdim + fdim;
			texCoords[arrIndex+6] = x*fdim;			texCoords[arrIndex+7] =  y*fdim + fdim;
			texCoords[arrIndex+8] = x*fdim + fdim;	texCoords[arrIndex+9] =  y*fdim;
			texCoords[arrIndex+10] = x*fdim + fdim;	texCoords[arrIndex+11] =  y*fdim+fdim;

			/*
				The following two if blocks handle moving to the next line (y) when out of room
			*/

			if(xCurrent + dxynorm >= xEnd)
			{
				textRow++;
				xCurrent = xStart;
			}

			//If the new word might get split, bump to next line
			if(text[vpos].dialogue[i] == ' ')
			{
				int wordStart = i;
				while(text[vpos].dialogue[wordStart] == ' ')
				{
					wordStart++;
				}

				int wordEnd = wordStart;
				while((text[vpos].dialogue[wordEnd] != ' ') && (text[vpos].dialogue[wordEnd] != '\0'))
				{
					wordEnd++;
				}

				if(xCurrent + (dxynorm - 0.5*globalOffset*scale) * (wordEnd - wordStart) > xEnd)
				{
					textRow++;
					xCurrent = xStart;
				}
			}

			/*
				Maps the vertices with offsets to improve the look of the text
			*/

			float ofs = offsets[mapPos]*scale;
			float mofs = ofs *0.5f; //Middle offset
			float newXCurrent = xCurrent + dxynorm + ofs - globalOffset*scale;

			//Avoids weird hanging spaces at the start of lines
			if(text[vpos].dialogue[i] == ' ' && (xCurrent == xStart))
			{
				newXCurrent = xStart;
			}
		
			vertices[arrIndex+0] = xCurrent + mofs;					vertices[arrIndex+1] = ynormResponses - (textRow+1)*dxynorm;
			vertices[arrIndex+2] = xCurrent +dxynorm + mofs;		vertices[arrIndex+3] = ynormResponses - (textRow+1)*dxynorm;
			vertices[arrIndex+4] = xCurrent + mofs;					vertices[arrIndex+5] = ynormResponses - textRow*dxynorm;
			vertices[arrIndex+6] = xCurrent + mofs;					vertices[arrIndex+7] = ynormResponses - textRow*dxynorm;
			vertices[arrIndex+8] = xCurrent +dxynorm + mofs;		vertices[arrIndex+9] = ynormResponses - (textRow+1)*dxynorm;
			vertices[arrIndex+10]= xCurrent +dxynorm + mofs;		vertices[arrIndex+11]= ynormResponses - textRow*dxynorm;

			xCurrent = newXCurrent;
		}

		/*
			Constructs the bounding box with relevant information and pushes it on the boxes vector
		*/

		y2 = ynormResponses - (textRow+1)*dxynorm;

		float halfWidth = screenWidth/2.0f;
		float halfHeight = screenHeight/2.0f;

		ix1 = (x1*(screenHeight/(float)screenWidth)+1) * halfWidth;
		ix2 = (x2*(screenHeight/(float)screenWidth)+1) * halfWidth;
		iy1 = screenHeight - (y1+1) * halfHeight;
		iy2 = screenHeight - (y2+1) * halfHeight;

		BoundingBox b(ix1, iy1, ix2, iy2);
		b.setUPos(x1, y1, x2, y2);
		boxes.push_back(b);

	}



	glGenBuffers(1, &textVertVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textVertVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numTextVerts, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &textTexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textTexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numTextVerts, texCoords, GL_STATIC_DRAW);

	glGenVertexArrays(1, &textVAO);
	glBindVertexArray(textVAO);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, textVertVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, textTexVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);


	/////////////

	genBox();
}

//std::vector<BoundingBox> Text::getBoundingBox();

//Returns the index of the Dialogue or text that contains a point, returns -1 if none found;
int Text::contains(double x, double y)
{
	for(int i = 0; i < boxes.size(); i++)
	{
		if(boxes[i].containsPoint(x, y))
		{
			return i;
		}
	}
	return -1;
}

GLuint Text::getTextVAO()
{
	return textVAO;
}

GLuint Text::getBoxVAO()
{
	return boxVAO;
}

void Text::reset()
{
	if(textVAO != NULL && boxVAO != NULL)
	{
		boxes.clear();

		glBindVertexArray(textVAO);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDeleteBuffers(1, &textTexVBO);
		glDeleteBuffers(1, &textVertVBO);
		glDeleteVertexArrays(1, &textVAO);

		glBindVertexArray(boxVAO);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDeleteBuffers(1, &boxVertVBO);
		glDeleteBuffers(1, &boxIdVBO);
		glDeleteVertexArrays(1, &boxVAO);
	}
}


Text::~Text(void)
{
	reset();
}
