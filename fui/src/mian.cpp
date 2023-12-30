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
#include "graphics/text.h"
#include "graphics/marker.h"

#include "graphics/models/rect.hpp"

fui::scene scene;

rect r1("r1");
rect r2("r2");

int main() {
    double st = glfwGetTime();
    scene.init();

    Shader shader("assets/shaders/object.vs", "assets/shaders/object.fs");
    Shader textShader("assets/shaders/text.vs", "assets/shaders/text.fs");
    Shader outlineShader ("assets/shaders/outline.vs", "assets/shaders/outline.fs");

    r1.init("assets/textures/shrek.jpg");
    scene.registerModel(&r1);
    r1.generateInstance(glm::vec2(0.25, 0.0), glm::vec2(0.5));
    r1.generateInstance(glm::vec2(-0.25, 0.0), glm::vec2(0.5));
    r1.generateInstance(glm::vec2(-0.25, 0.0), glm::vec2(0.125));
    r1.initInstances();


    r2.init(glm::vec3(0.1, 0.1, 0.1));
    scene.registerModel(&r2);
    r2.generateInstance(glm::vec2(0.25, 0.5), glm::vec2(0.5));
    r2.generateInstance(glm::vec2(-0.25, 0.0), glm::vec2(0.25));
    r2.initInstances();

    r2.instances[1]->setParent(r1.instances[1]);
    r1.instances[2]->setParent(r2.instances[1]);

    std::cout << "Everything started in: "<< glfwGetTime() - st << "sec. Now the program can be used." << std::endl;
    while (!scene.shouldClose())
    {
        scene.update();
        scene.renderScene(shader, outlineShader, textShader);
        scene.newFrame();
    }
    scene.terminate();
    scene.cleanup();
	return 0;
}