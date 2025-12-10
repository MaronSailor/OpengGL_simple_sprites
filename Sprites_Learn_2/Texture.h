#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>


class Texture {
public:
	GLuint textureId;
	GLuint textureWidth, textureHeight;

	const int horizontalFrameCount = 16;
	const int verticalFrameCount = 16;

	~Texture();
	Texture();

	void loadTexture(const GLchar* texPath);
	void bindTexture();

};