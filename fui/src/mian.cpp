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

Shader outlineShader;
void processInput();

int main() {
    scene.init();

    Shader shader("assets/shaders/object.vs", "assets/shaders/object.fs");
    outlineShader = Shader("assets/shaders/outline.vs", "assets/shaders/outline.fs");

    r.init();
    r.generateInstance(glm::vec2(0.25, 0.0), glm::vec2(0.5));
    r.generateInstance(glm::vec2(-0.25, 0.0), glm::vec2(0.5));
    r.initInstances();

    while (!scene.shouldClose())
    {
        scene.update();

        processInput();
        
        //r.prepareOutlineShader(outlineShader);
        r.renderInstances(shader);
        r.renderOutlineShaderQueue(outlineShader);

        scene.newFrame();
    }

    scene.terminate();
	return 0;
}

void processInput() {
    scene.processInput();

    for (int i = 0; i < r.instances.size(); i++) {
        r.instances[i]->interactivity.update();
    }
}