#include "uiinteractivity.h"
#include "transform2d.h"
#include "../graphics/fuiscene.h"
#include "selectedItemManager.h"


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
    if (scene::mouseButtonWentDown(GLFW_MOUSE_BUTTON_1) && instance->border.isDotInRect(mousePos) && sim->canBeSelected(instance)) {
        sim->selectedItem = instance;
        sim->makeMeFirstInRender(instance->model);
        instance->orderInLayer = 1;

        isSelected = true;
        if (instance->border.isPointCloseToBorder(mousePos, distToOutline)) {
            isResizing = true;
            calculateResize(mousePos);
            sim->setResizing(this);
        }
        click();
    }
    else if (instance->border.isPointCloseToBorder(mousePos, distToOutline) && sim->canBeSelected(instance)) {
        instance->model->addToOutlineShaderQueue(instance->model->getInstaneIdxById(instance->indstanceId), glm::vec3(0.01, 0.42, 0.17));

        sim->makeMeFirstInOutline(instance->model);
        if (sim->getResizing() && sim->getResisingObject() != this) {
            sim->sendWishPos(instance->border.getCoordOfContactBorder(mousePos, distToOutline), this);
        }
    }
    if (scene::mouseButtonWentUp(GLFW_MOUSE_BUTTON_1)) {
        if (sim->selectedItem == instance) {
            instance->orderInLayer = 0;
            sim->offResizing();
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

void fui::uiinteractivity::setResizeWishPos(glm::vec2 pos) {
    glm::vec2 offset = glm::vec2(0);
    glm::vec2 min = instance->border.min;
    glm::vec2 max = instance->border.max;
    if (quaterK.x > 0) 
        offset = glm::vec2(pos.x - max.x, offset.y);
    if (quaterK.x < 0)
        offset = glm::vec2(pos.x - min.x, offset.y);

    if (quaterK.y > 0)
        offset = glm::vec2(offset.x, pos.y - max.y);
    if (quaterK.y < 0)
        offset = glm::vec2(offset.x, pos.y - min.y);

    offset *= quaterK;

    instance->changeSizeInNDC(offset);
    instance->addPositionInPixels(glm::vec2(offset.x * scene::width, offset.y * scene::height) * 0.25f * quaterK);
}

void fui::uiinteractivity::click() {
    for (auto& fn : funcsOnClick_none) {
        fn();
    }
    for (auto& fn : funcsOnClick_int) {
        fn.first(fn.second);
    }
}

void fui::uiinteractivity::setSIM(selectedItemManager* SIM) {
    sim = SIM;
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