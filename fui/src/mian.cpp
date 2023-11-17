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

rect r(scene);

Shader outlineShader;

void processInput();
int main() {
    scene.init();

    Shader shader("assets/shaders/object.vs", "assets/shaders/object.fs");
    outlineShader = Shader("assets/shaders/outline.vs", "assets/shaders/outline.fs");

    r.init();
    r.generateInstance(glm::vec2(0.0), glm::vec2(0.5));
    r.initInstances();
    float lastTime = glfwGetTime();
    while (!scene.shouldClose())
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        std::cout << "FPS: " << (int)(1 / deltaTime)<< std::endl;

        scene.update();

        processInput();
        
        r.renderShadersQueue();
        r.renderInstances(shader);

        scene.newFrame();
    }

    scene.terminate();
	return 0;
}

void processInput() {
    scene.processInput();

    if (Mouse::button(GLFW_MOUSE_BUTTON_1)) {
        for (int i = 0; i < r.instances.size(); i++) {
            if (r.instances[i]->border.isDotInRect(scene.getMousePosInNDC())) {
                float x = Mouse::getDX();
                float y = Mouse::getDY();
                if(r.instances[i]->border.getDistFromPointToBorder(scene.getMousePosInNDC()) < 0.2)
                    r.addToShadersQueue(outlineShader, i);
                r.instances[i]->addPositionInPixels(glm::vec2(x, y));
            }
        }
    }
}