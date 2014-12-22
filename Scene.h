#pragma once

#define CHARACTER 0
#define ENVIRONMENT 1
#define GUI 2

#include <GLFW/glfw3.h>
#include <vector>
#include "BoundingBox.h"

class Scene
{
public:
	Scene(void);
	//Leave textureBounds or sceneBounds NULL for max value
	Scene(GLuint texture, BoundingBox& textureBounds, BoundingBox& sceneBounds, int width, int height);
	
	Scene(BoundingBox& sceneBounds, int width, int height);
	void setTexture(int texture);
	
	//leave NULL for no texture
	void genVAO(BoundingBox& textureBounds);
	void genVAO();
	void addBoundingBox(BoundingBox& bounds, int leadsTo);

	GLuint getVAO();
	int getNumVerts();
	bool usesTexture();

	GLuint getTexture();
	
	int contains(double x, double y);

	~Scene(void);

	float color[3]; //For use without texture
	float pos[2];
	float rot[2];
	float scale;

private:
	int id;
	GLuint tex; //texture


	std::vector<BoundingBox> boxes; //The first box is ALWAYS the box surrounding the scene

	bool usesTex;

	int numVerts;
	GLuint sceneVAO;
	GLuint vertVBO;
	GLuint texVBO;



	

};

