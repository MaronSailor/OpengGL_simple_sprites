#include "Shaders.h"

Shader::Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
{
	GLint success;
	programId = 0;

	GLuint vertexShader = shaderCompile(GL_VERTEX_SHADER, loadFile(vertexShaderPath).c_str());
	GLuint fragmentShader = shaderCompile(GL_FRAGMENT_SHADER, loadFile(fragmentShaderPath).c_str());

	programId = glCreateProgram();
	glAttachShader(programId, vertexShader);
	glAttachShader(programId, fragmentShader);
	glLinkProgram(programId);

	glGetShaderiv(programId, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(programId, 512, 0, infoLog);
		std::cerr << "ERROR: could not link program\n" << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Program was linked\n";

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

Shader::~Shader() {

}

void Shader::shaderUse()
{
	glUseProgram(programId);
}

std::string Shader::loadFile(const GLchar* filePath)
{
	std::fstream file(filePath);

	if (!file) {
		std::cerr << "ERROR: could not open file " << filePath << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "File " << filePath << " was opened\n";
	

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint Shader::shaderCompile(GLenum shaderType,  const GLchar* shaderSource)
{
	GLuint shader;
	GLint success;

	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, 0, infoLog);
		std::cerr << "ERROR: could not compile shader\n" << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Shader was compiled\n";

	return shader;
}
