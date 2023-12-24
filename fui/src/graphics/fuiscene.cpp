#include "fuiscene.h"

unsigned int fui::scene::width = 0;
unsigned int fui::scene::height = 0;
fui::rectBorder2D fui::scene::border = rectBorder2D(glm::vec2(-1.0), glm::vec2(1.0));

double fui::scene::mouseDX = 0;
double fui::scene::mouseDY = 0;

bool fui::scene::mouseButtons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool fui::scene::mouseButtonsWentUp[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool fui::scene::mouseButtonsWentDown[GLFW_MOUSE_BUTTON_LAST] = { 0 };


void fui::scene::framebufferSizeCallback(GLFWwindow* widnow, int width, int height) {
    glViewport(0, 0, width, height);
    // update variables
    scene::width = width;
    scene::height = height;

    //fui::scene::border = rectBorder2D(glm::vec2(0.0), glm::vec2(width, height));
}
fui::scene::scene(int width, int height, const char* title, glm::vec4 color)
    : title(title), windowColor(color), iAmParent(new parent(&fui::scene::border)) {

    fui::scene::width = width;
    fui::scene::height = height;
    //fui::scene::border = rectBorder2D(glm::vec2(0.0), glm::vec2(width, height));
}
int fui::scene::init() {
    float startTime = glfwGetTime();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "GLFW window was created." << std::endl;
    glfwMakeContextCurrent(window);
    //glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "GLAD was initialized." << std::endl;

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

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (FT_Init_FreeType(&ft)) {
        std::cout << "Could not init FreeType library" << std::endl;
        return false;
    }
    std::cout << "FreeType was loaded." << std::endl;
    textRenderer = TextRenderer(20);
    if (!textRenderer.loadFont(ft, "assets/fonts/courer.ttf")) {
        std::cout << "Could not load font" << std::endl;
        return false;
    }
    std::cout << "Text renderer created." << std::endl;
    FT_Done_FreeType(ft);

    std::cout << "Program started in " << glfwGetTime() - startTime << " sec.\n" << std::endl;

    return 0;
}
bool fui::scene::shouldClose() {
    return glfwWindowShouldClose(window);
}
void fui::scene::registerModel(model2D* model) {
    model->root = iAmParent;
    models.push_back(model);
    std::cout << "Model '" << model->id << "' was registered." << std::endl;
}
void fui::scene::registerMarker(circle* m) {
    //m->sim = &sim;
    //for (transform2D* instance : m->instances) {
    //    instance->interactivity.setSIM(m->sim);
    //}
    //marker = m;
}
void fui::scene::update() {
    glClearColor(windowColor[0], windowColor[1], windowColor[2], windowColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    rememberMouseInputs();

    processInput();
    for (model2D* model : models) {
        for (transform2D* instance : model->instances) {
            instance->interactivity.update();
        }
    }
}
void fui::scene::renderScene(Shader shader, Shader outlineShader, Shader textShader) {
    iAmParent->renderChildren(shader, outlineShader);
    /*for (model2D* model : sim.renderQueue) {
        model->renderInstances(shader);
    }
    for (model2D* model : sim.outlineQueue) {
        model->renderOutlinedInstances(shader, outlineShader);
    }
    for (glm::vec2 pos : sim.markerPositions) {
        marker->generateInstance(pos, glm::vec2(0.02));
    }
    marker->renderInstances(shader);
    if (sim.markerPositions.size() > 0)
        sim.markerPositions.clear();
    marker->clearInstances();*/
    //textRenderer.render(textShader, "Hello", 100, 100, glm::vec2(10.0, 5.0), glm::vec3(1.0));
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
void fui::scene::cleanup() {
    for (model2D* model : models) {
        model->cleanup();
    }
}
fui::model2D* fui::scene::getModelById(std::string modelId) {
    for (model2D* model : models) {
        if (model->id == modelId)
            return model;
    }
    return nullptr;
}
glm::vec2 fui::scene::getMousePosInNDC() {
    int x = Mouse::getMouseX();
    int y = Mouse::getMouseY();

    double x2s = x / (double)fui::scene::width;
    double y2s = y / (double)fui::scene::height;

    return glm::vec2((x2s - 0.5f) * 2, - (y2s - 0.5f) * 2);
}
glm::vec2 fui::scene::getMousePosInPixels() {
    glm::vec2 res = glm::vec2(Mouse::getMouseX(), 800.0 - Mouse::getMouseY());
    return res;
}
void fui::scene::rememberMouseInputs() {
    mouseDX = Mouse::getDX();
    mouseDY = Mouse::getDY();

    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) {
        mouseButtons[i] = Mouse::button(i);
        mouseButtonsWentUp[i] = Mouse::buttonWentUp(i);
        mouseButtonsWentDown[i] = Mouse::buttonWentDown(i);
    }
}
double fui::scene::getDX() {
    return mouseDX;
}
double fui::scene::getDY() {
    return mouseDY;
}
bool fui::scene::mouseButton(int button) {
    return mouseButtons[button];
}
bool fui::scene::mouseButtonWentUp(int button) {
    return mouseButtonsWentUp[button];
}
bool fui::scene::mouseButtonWentDown(int button) {
    return mouseButtonsWentDown[button];
}