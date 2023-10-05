#include <iostream>

#include <vector>

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

void processInput();
int main() {
    scene.init();

    Shader shader("assets/shaders/object.vs", "assets/shaders/object.fs");
    r.init();
    r.generateInstance(glm::vec2(0.0));
    r.initInstances();
    while (!scene.shouldClose())
    {
        scene.update();

        processInput();

        shader.activate();
        r.renderInstances(shader);

        scene.newFrame();
    }

    scene.terminate();
	return 0;
}

void processInput() {
    scene.processInput();


    if (Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_1)) {
        std::cout << r.border.isDotInRect(scene.getMousePosInNDC()) << std::endl;
    }
}