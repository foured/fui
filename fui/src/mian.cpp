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
#include "graphics/text.h"

fui::scene scene;

rect r;

void processInput();
void cleanup();

int main() {
    scene.init();

    Shader shader("assets/shaders/object.vs", "assets/shaders/object.fs");
    Shader textShader("assets/shaders/text.vs", "assets/shaders/text.fs");
    Shader outlineShader ("assets/shaders/outline.vs", "assets/shaders/outline.fs");

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


        r.renderInstances(shader, outlineShader);
        scene.textRenderer.render(textShader, "Hello", 100, 100, glm::vec2(10.0, 5.0), glm::vec3(1.0));

        scene.newFrame();
        endTime = glfwGetTime();
        std::cout << std::string(fpsmsg.length(), '\b');
        fpsmsg = "fps: " + std::to_string((1 / (endTime - startTime))) + " frame time: " + std::to_string(endTime - startTime);
        std::cout << fpsmsg;
    }

    scene.terminate();
    cleanup();
	return 0;
}

void processInput() {
    scene.processInput();

    for (int i = 0; i < r.instances.size(); i++) {
        r.instances[i]->interactivity.update();
    }
}

void cleanup() {
    r.cleanup();
}