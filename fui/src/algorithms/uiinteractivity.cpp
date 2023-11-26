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

void fui::uiinteractivity::update() {

    float x = scene::getDX();
    float y = scene::getDY();
    glm::vec2 mousePos = scene::getMousePosInNDC();
    if (scene::mouseButtonWentDown(GLFW_MOUSE_BUTTON_1) && instance->border.isDotInRect(mousePos) && instance->model->canBeSelected(instance)) {
        instance->model->selectedInstanceId = instance->indstanceId;
        instance->orderInLayer = 1;

        isSelected = true;
        isResizing = instance->border.isPointCloseToBorder(mousePos, distToOutline);
        calculateResize(mousePos);

        click();
    }
    else if (instance->border.isPointCloseToBorder(mousePos, distToOutline) && instance->model->canBeSelected(instance)) {
        instance->model->addToOutlineShaderQueue(instance->model->getInstaneIdxById(instance->indstanceId), glm::vec3(0.01, 0.42, 0.17));
    }
    if (scene::mouseButtonWentUp(GLFW_MOUSE_BUTTON_1)) {
        if (instance->model->selectedInstanceId == instance->indstanceId) {
            instance->orderInLayer = 0;
        }
        isSelected = false;
        isResizing = false;
    }
    

    drag(x, y);
    resize(x, y, mousePos);
}

void fui::uiinteractivity::drag(float mouseDX, float mouseDY) {
	if (isDraggable && isSelected && !isResizing) {
        instance->addPositionInPixels(glm::vec2(mouseDX, mouseDY));
	}
}

void fui::uiinteractivity::resize(float mouseDX, float mouseDY, glm::vec2 mousePos) {
    if (isResizeable && isSelected) {
        if (isResizing) {
            instance->model->addToOutlineShaderQueue(instance->model->getInstaneIdxById(instance->indstanceId), glm::vec3(0.0, 0.8, 0.1));
            glm::vec2 m = instance->changeSizeAndGetMultiplier(glm::vec2(mouseDX, mouseDY) * quaterK);
            instance->addPositionInPixels(glm::vec2(mouseDX * xk, mouseDY * yk) * 0.25f * quaterK * m);
        }
    }
}

void fui::uiinteractivity::click() {
    for (auto& fn : funcsOnClick_none) {
        fn();
    }
    for (auto& fn : funcsOnClick_int) {
        fn.first(fn.second);
    }
}

void fui::uiinteractivity::calculateResize(glm::vec2 mousePos) {
    yk = 1, xk = 1;
    if (mousePos.x < instance->position.x) xk = -1;
    if (mousePos.y < instance->position.y) yk = -1;
    quaterK = instance->border.getQuatersOfBorderContactWithPoint(mousePos, distToOutline);
}

void fui::uiinteractivity::addFunctionOnClick(std::function<void(int)> func, int arg) {
    funcsOnClick_int.emplace_back(func, arg);
}

void fui::uiinteractivity::addFunctionOnClick(std::function<void()> func) {
    funcsOnClick_none.push_back(func);
}