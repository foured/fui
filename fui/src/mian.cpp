#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/fuiscene.h"

fui::scene scene;

void processInput();
int main() {
    scene.init();

    while (!scene.shouldClose())
    {
        scene.update();

        processInput();

        scene.newFrame();
    }

    scene.terminate();
	return 0;
}

void processInput() {
    scene.processInput();
}