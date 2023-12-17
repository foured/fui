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

#include "graphics/models/rect.hpp"
#include "graphics/models/circle.hpp"

fui::scene scene;

rect r1("r1");
rect r2("r2");
circle c;

int main() {
    scene.init();

    Shader shader("assets/shaders/object.vs", "assets/shaders/object.fs");
    Shader textShader("assets/shaders/text.vs", "assets/shaders/text.fs");
    Shader outlineShader ("assets/shaders/outline.vs", "assets/shaders/outline.fs");

    r2.init(glm::vec3(0.1, 0.1, 0.1));
    r2.generateInstance(glm::vec2(0.25, 0.5), glm::vec2(0.5));
    r2.initInstances();
    scene.registerModel(&r2);

    r1.init("assets/textures/shrek.jpg");
    r1.generateInstance(glm::vec2(0.25, 0.0), glm::vec2(0.5));
    r1.generateInstance(glm::vec2(-0.25, 0.0), glm::vec2(0.5));
    r1.initInstances();
    scene.registerModel(&r1);

    c.init(16, glm::vec3(1, 0, 0));
    scene.registerMarker(&c);

    double startTime, endTime;
    std::string fpsmsg;
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