#include "fuiscene.h"

unsigned int fui::scene::width = 0;
unsigned int fui::scene::height = 0;

void fui::scene::framebufferSizeCallback(GLFWwindow* widnow, int width, int height) {
    glViewport(0, 0, width, height);
    // update variables
    scene::width = width;
    scene::height = height;
}

fui::scene::scene(int width, int height, const char* title, glm::vec4 color)
    : title(title), windowColor(color) {

    fui::scene::width = width;
    fui::scene::height = height;
}

int fui::scene::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, width, height);

    // frame size
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    // key pressed
    glfwSetKeyCallback(window, Keyboard::keyCallback);
    // cursor moved
    glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
    // mouse btn pressed
    glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
    // mouse scroll
    glfwSetScrollCallback(window, Mouse::mouseWheelCallback);

    std::cout << "Program started." << std::endl;

    return 0;
}

bool fui::scene::shouldClose() {
    return glfwWindowShouldClose(window);
}

void fui::scene::update() {
    glClearColor(windowColor[0], windowColor[1], windowColor[2], windowColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void fui::scene::newFrame() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void fui::scene::terminate() {
    glfwTerminate();
}

void fui::scene::setShouldClose(bool value) {
    glfwSetWindowShouldClose(window, value);
}

void fui::scene::processInput() {
    if (Keyboard::key(GLFW_KEY_ESCAPE)) {
        setShouldClose(true);
    }
}
