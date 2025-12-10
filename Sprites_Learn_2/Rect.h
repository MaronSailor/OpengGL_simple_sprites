#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include "Texture.h"


class Rect
{
public:
	Rect();
	~Rect();
	
Texture texture;
	GLfloat Vertices[16];
	GLint Indices[6];

	float u0, u1, v0, v1;

	void drawRect();
	void rectInit();
	void updateRect();
	void setFrame(int frameIndex);

private:
	GLuint VBO, VAO, EBO, CBO;
};
