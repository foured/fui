#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/fuiscene.h"
#include "graphics/shader.h"
#include "graphics/mesh2d.h"

#include "graphics/models/rect.hpp"

fui::scene scene;

rect r;

Shader outlineShader;
void processInput();

void printOne(int q);

int main() {
    scene.init();

    Shader shader("assets/shaders/object.vs", "assets/shaders/object.fs");
    outlineShader = Shader("assets/shaders/outline.vs", "assets/shaders/outline.fs");

    r.init();
    r.generateInstance(glm::vec2(0.25, 0.0), glm::vec2(0.5));
    r.generateInstance(glm::vec2(-0.25, 0.0), glm::vec2(0.5));
    r.initInstances();

    double startTime, endTime;
    std::string fpsmsg;
    while (!scene.shouldClose())
    {
        startTime = glfwGetTime();

        scene.update();

        processInput();

        //glStencilFunc(GL_ALWAYS, 1, 0xFF);
        //glStencilMask(0xFF);
        r.renderInstances(shader, outlineShader);
        //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        //glStencilMask(0x00);
        //outlineShader.activate();
        //r.renderInstances(shader);
        //glStencilMask(0xFF);
        //glStencilFunc(GL_ALWAYS, 1, 0xFF);
        //r.renderOutlineShaderQueue(outlineShader);

        scene.newFrame();

        endTime = glfwGetTime();
        std::cout << std::string(fpsmsg.length(), '\b');
        fpsmsg = "frame start: " + std::to_string(startTime) + " frame end: " + std::to_string(endTime) + "fps: " + std::to_string(1.0 / (endTime - startTime));
        std::cout << fpsmsg;
    }

    scene.terminate();
	return 0;
}

void printOne(int q) {
    std::cout << sizeof(int) << std::endl;
}

void processInput() {
    scene.processInput();

    for (int i = 0; i < r.instances.size(); i++) {
        r.instances[i]->interactivity.update();
    }
}