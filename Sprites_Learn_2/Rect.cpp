#include "Rect.h"

Texture texture;


Rect::Rect() {


	u0 = 0.0f;
	u1 = 1.0f / texture.horizontalFrameCount;
	v0 = 0.0f;
	v1 = 1.0f / texture.verticalFrameCount; 


	unsigned int bufferIndices[] = {
								0, 1, 2,	   // First Triagnle
								0, 2, 3		   // Second Triangle
								};
	std::copy(std::begin(bufferIndices), std::end(bufferIndices), Indices);
}

void Rect::updateRect()
{
	GLfloat bufferVertices[] = {// x	  y	  u  v
								 0.5f, -0.5f, u1, v0,// Bottom Right
								-0.5f, -0.5f, u0, v0,// Bottom Left
								-0.5f,  0.5f, u0, v1,// Top Left
								 0.5f,  0.5f, u1, v1// Top Right
	};
	std::copy(std::begin(bufferVertices), std::end(bufferVertices), Vertices);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Rect::setFrame(int frameIndex)
{
	 int col = frameIndex % texture.horizontalFrameCount;   
    int row = frameIndex / texture.horizontalFrameCount;  

    u0 = col / (float)texture.horizontalFrameCount;
    u1 = u0 + 1.0f / texture.horizontalFrameCount;

    v0 = 1.0f - (row + 1) / (float)texture.verticalFrameCount;
    v1 = v0 + 1.0f / texture.verticalFrameCount;

	updateRect();
}


Rect::~Rect()
{
}

void Rect::drawRect()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Rect::rectInit()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(sizeof(GLfloat)*2));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
}

