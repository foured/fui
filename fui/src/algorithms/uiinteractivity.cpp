#include "uiinteractivity.h"
#include "transform2d.h"

fui::uiinteractivity::uiinteractivity(){}

fui::uiinteractivity::uiinteractivity(transform2D* transform) 
    : instance(transform) {
	isDraggable = true;
	isResizeable = true;
    isSelected = false;
    distToOutline = 0.02;

    isResizing = false;
}

void fui::uiinteractivity::update(Shader outlineShader) {
    float x = Mouse::getDX();
    float y = Mouse::getDY();
    glm::vec2 mousePos = fui::scene::getMousePosInNDC();

    if (Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_1) && instance->border.isDotInRect(mousePos)) {
        isSelected = true;
        isResizing = instance->border.isPointCloseToBorder(mousePos, distToOutline);
        calculateResize(mousePos);
    }
    if (Mouse::buttonWentUp(GLFW_MOUSE_BUTTON_1)) {
        isSelected = false;
        isResizing = false;
    }
    

    drag(x, y);
    resize(outlineShader, x, y, mousePos);
}

void fui::uiinteractivity::drag(float mouseDX, float mouseDY) {
	if (isDraggable && isSelected && !isResizing) {
        instance->addPositionInPixels(glm::vec2(mouseDX, mouseDY));
	}
}

void fui::uiinteractivity::resize(Shader outlineShader, float mouseDX, float mouseDY, glm::vec2 mousePos) {
    if (isResizeable && isSelected) {
        if (isResizing) {
            instance->model->addToShadersQueue(outlineShader, instance->model->getInstaneIdxById(instance->indstanceId));
            instance->changeSize(glm::vec2(mouseDX, mouseDY) * quaterK);
            instance->addPositionInPixels(glm::vec2(mouseDX * xk, mouseDY * yk) * 0.25f * quaterK);
        }
    }
}
void fui::uiinteractivity::calculateResize(glm::vec2 mousePos) {
    yk = 1, xk = 1;
    if (mousePos.x < instance->position.x) xk = -1;
    if (mousePos.y < instance->position.y) yk = -1;
    quaterK = instance->border.getQuatersOfBorderContactWithPoint(mousePos, distToOutline);
}