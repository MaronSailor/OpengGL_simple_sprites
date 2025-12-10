#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>



class Shader
{
public:
	Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
	~Shader();


	void shaderUse();
	std::string loadFile(const GLchar* filePath);
	GLuint programId;
private:
	GLuint shaderCompile(GLenum shaderType, const GLchar* shaderPath);
};
