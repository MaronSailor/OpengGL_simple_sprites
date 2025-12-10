#include "Scene.h"

Rect rect;
Shader* shader;
Scene* Scene::instance = nullptr;

Scene::Scene(int argc, char** argv) : windowWidth(800), windowHeight(600) {
    instance = this;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Window");

    if (glewInit() != GLEW_OK) {
        std::cerr << "ERROR: GLEW could not be initialised\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "GLEW was initialised\n";

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl");

    rect.rectInit();
    rect.texture.loadTexture("KNIGHT.png");

    // Start timer loop for animation
    glutTimerFunc(100, updateFrame, 0);

    // Register callbacks
    glutDisplayFunc(Scene::renderWindow);
    glutIdleFunc(Scene::renderWindow);
    glutReshapeFunc(Scene::reshapeWindow);
    glutKeyboardFunc(Scene::handleKeyboard);

    glutMainLoop();
}

Scene::~Scene() {}

void Scene::renderWindow() {
    glClearColor(0.5f, 0.5f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, rect.texture.textureId);
    shader->shaderUse();

    if (instance) {
        int currentFrame = instance->hero.anim.getCurrentFrame();
        rect.setFrame(currentFrame);
    }

    rect.drawRect();
    glutSwapBuffers();
}

void Scene::reshapeWindow(int w, int h) {
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void Scene::updateFrame(int value) {
    if (instance) {
        instance->hero.anim.update(0.1f); // ~100ms per tick
    }
    glutTimerFunc(100, updateFrame, 0);
}

void Scene::handleKeyboard(unsigned char key, int x, int y) {
    if (!instance) return;

    switch (key) {
    case 'a': instance->hero.anim.play("WALK FRONT"); break;
    case 'w': instance->hero.anim.play("WALK BACK"); break;
    case 'q': exit(EXIT_SUCCESS);
    case ' ': instance->hero.anim.play("HURT FRONT"); break;
    default:  instance->hero.anim.play("STAND"); break;
    }
}
