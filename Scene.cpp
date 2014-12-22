#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Scene.h"


Scene::Scene(void)
{
	tex = 0;
	id = -1;
	color[0] = color[1] = color[2] = 0;
	pos[0] = pos[1] = 0;
	rot[0] = rot[1] = 0;

	numVerts = 0;
	sceneVAO = 0;
	vertVBO = 0;
	texVBO = 0;
	scale = 1;
}

Scene::Scene(GLuint texture,  BoundingBox& textureBounds, BoundingBox& sceneBounds, int width, int height)
{
	color[0] = color[1] = color[2] = 0;
	pos[0] = pos[1] = 0;
	rot[0] = rot[1] = 0;
	scale = 1;

	tex = texture;

	boxes.push_back(sceneBounds);

	boxes[0].x1 = (boxes[0].fx1+1.0f)*0.5f*width;
	boxes[0].x2 = (boxes[0].fx2+1.0f)*0.5f*width;

	boxes[0].y1 = height - (boxes[0].fy1+1.0f)*0.5f*height;
	boxes[0].y2 = height - (boxes[0].fy2+1.0f)*0.5f*height;

	genVAO(textureBounds);
}

Scene::Scene(BoundingBox& sceneBounds, int width, int height)
{
	color[0] = color[1] = color[2] = 0;
	pos[0] = pos[1] = 0;
	rot[0] = rot[1] = 0;

	boxes.push_back(sceneBounds);

	boxes[0].x1 = (boxes[0].fx1+1.0f)*0.5f*width;
	boxes[0].x2 = (boxes[0].fx2+1.0f)*0.5f*width;

	boxes[0].y1 = height - (boxes[0].fy1+1.0f)*0.5f*height;
	boxes[0].y2 = height - (boxes[0].fy2+1.0f)*0.5f*height;

	genVAO();
}

GLuint Scene::getVAO()
{
	return sceneVAO;
}

bool Scene::usesTexture()
{
	return usesTex;
}

int Scene::getNumVerts()
{
	return numVerts;
}

GLuint Scene::getTexture()
{
	return tex;
}

int Scene::contains(double x, double y)
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

void Scene::genVAO(BoundingBox& textureBounds)
{
	numVerts = 12;
	GLfloat* vertices = new GLfloat[12];
	GLfloat* texCoords = new GLfloat[12];

	vertices[0] = boxes[0].fx1;		vertices[1] = boxes[0].fy2;
	vertices[2] = boxes[0].fx2;		vertices[3] = boxes[0].fy2;
	vertices[4] = boxes[0].fx1;		vertices[5] = boxes[0].fy1;
	vertices[6] = boxes[0].fx1;		vertices[7] = boxes[0].fy1;
	vertices[8] = boxes[0].fx2;		vertices[9] = boxes[0].fy2;
	vertices[10]= boxes[0].fx2;		vertices[11]= boxes[0].fy1;

	texCoords[0] = textureBounds.fx1;		texCoords[1] = textureBounds.fy2;
	texCoords[2] = textureBounds.fx2;		texCoords[3] = textureBounds.fy2;
	texCoords[4] = textureBounds.fx1;		texCoords[5] = textureBounds.fy1;
	texCoords[6] = textureBounds.fx1;		texCoords[7] = textureBounds.fy1;
	texCoords[8] = textureBounds.fx2;		texCoords[9] = textureBounds.fy2;
	texCoords[10]= textureBounds.fx2;		texCoords[11]= textureBounds.fy1;

	glGenBuffers(1, &vertVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*12, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &texVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*12, texCoords, GL_STATIC_DRAW);

	glGenVertexArrays(1, &sceneVAO);
	glBindVertexArray(sceneVAO);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	usesTex = true;

	delete[] vertices;
	delete[] texCoords;
}

void Scene::genVAO()
{
	numVerts = 12;
	GLfloat* vertices = new GLfloat[12];

	vertices[0] = boxes[0].fx1;		vertices[1] = boxes[0].fy2;
	vertices[2] = boxes[0].fx2;		vertices[3] = boxes[0].fy2;
	vertices[4] = boxes[0].fx1;		vertices[5] = boxes[0].fy1;
	vertices[6] = boxes[0].fx1;		vertices[7] = boxes[0].fy1;
	vertices[8] = boxes[0].fx2;		vertices[9] = boxes[0].fy2;
	vertices[10]= boxes[0].fx2;		vertices[11]= boxes[0].fy1;

	glGenBuffers(1, &vertVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*12, vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &sceneVAO);
	glBindVertexArray(sceneVAO);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	usesTex = false;

	delete[] vertices;
}

Scene::~Scene(void)
{
}
