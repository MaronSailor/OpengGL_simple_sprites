#pragma once
#include <GL/glew.h>
#include <GL/glut.h>	
#include "Shaders.h"
#include "Rect.h"
#include "Texture.h"
#include "Character.h"

#include <iostream>

class Scene
{
public:
	Scene(int argc, char**argv);
	~Scene();


	static void renderWindow();
	static void reshapeWindow(int w, int h);
	static void updateFrame(int value);
	static void handleKeyboard(unsigned char key, int x, int y);

	static Scene* instance;
	Character hero;

private:
	int windowWidth, windowHeight;
};

