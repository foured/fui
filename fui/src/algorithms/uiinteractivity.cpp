#include "uiinteractivity.h"
#include "transform2d.h"
#include "../graphics/fuiscene.h"


fui::uiinteractivity_config::uiinteractivity_config(uiinteractivity_config_type type) {
    if (type == uiinteractivity_config_type::DISABLE_ALL) {
        isResizeable = false;
        isDraggable = false;
        haveOutline = false;
    }
    else {
        isResizeable = true;
        isDraggable = true;
        haveOutline = true;
    }
    distToOutline = 0.02;
}
fui::uiinteractivity::uiinteractivity() {}
fui::uiinteractivity::uiinteractivity(transform2D* transform, uiinteractivity_config config)
    : instance(transform), config(config) {

    isSelected = false;
    isResizing = false;
    isDragging = false;
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
        if (instance->border.isPointCloseToBorder(mousePos, config.distToOutline)
            && instance->border.getQuatersOfBorderContactWithPoint(mousePos, config.distToOutline) != glm::vec2(0, 1)) {
            isResizing = true;
            calculateResize(mousePos);
            sim->action.setAction(selectedItemAction_type::RESIZING, this);
        }
        else if (instance->border.isPointCloseToBorder(mousePos, config.distToOutline)) {
            isDragging = true;
            sim->action.setAction(selectedItemAction_type::DRAGGING, this);
        }
        click();
    }
    else if (instance->border.isPointCloseToBorder(mousePos, config.distToOutline) && sim->canBeSelected(instance)) {
        if (sim->action.getIsInAction() && sim->action.type == selectedItemAction_type::RESIZING && sim->action.getActionObject() != this) {
            sim->action.sendWishPos(instance->border.getCoordOfContactBorder(mousePos, config.distToOutline), this);
        }
        else {
            if (config.haveOutline)
                instance->model->addToOutlineShaderQueue(instance->model->getInstaneIdxById(instance->indstanceId), glm::vec3(0.01, 0.42, 0.17));
            sim->makeMeFirstInOutline(instance->model);
        }
    }
    else if(sim->action.getIsInAction() && sim->action.type == selectedItemAction_type::DRAGGING && sim->action.getActionObject() != this){
        transform2D* aInstance = sim->action.getActionObject()->instance;

        if (instance->border.isPointCloseToBorderOutside(mousePos, config.distToOutline * 2)) { //top
            glm::vec2 contact = instance->border.getCoordOfContactBorderOutSide(mousePos, config.distToOutline * 2);
            sim->action.sendWishPos(contact, this);
            sim->action.setDopData(glm::vec2(contact.x, aInstance->border.max.y));
        }
        else if (instance->border.isPointCloseToBorderOutside(glm::vec2(aInstance->border.max.x, aInstance->border.origin.y), config.distToOutline * 2)) { //right
            glm::vec2 contact = instance->border.getCoordOfContactBorderOutSide(glm::vec2(aInstance->border.max.x, aInstance->border.origin.y), config.distToOutline * 2);
            sim->action.sendWishPos(contact, this);
            sim->action.setDopData(glm::vec2(aInstance->border.max.x, contact.y));
        }
        else if (instance->border.isPointCloseToBorderOutside(glm::vec2(aInstance->border.min.x, aInstance->border.origin.y), config.distToOutline * 2)) { //left
            glm::vec2 contact = instance->border.getCoordOfContactBorderOutSide(glm::vec2(aInstance->border.min.x, aInstance->border.origin.y), config.distToOutline * 2);
            sim->action.sendWishPos(contact, this);
            sim->action.setDopData(glm::vec2(aInstance->border.min.x, contact.y));
        }
    }
    if (scene::mouseButtonWentUp(GLFW_MOUSE_BUTTON_1)) {
        if (sim->selectedItem == instance) {
            instance->orderInLayer = 0;
            sim->action.offAction();
        }
        isSelected = false;
        isResizing = false;
        isDragging = false;
    }
    

    drag(x, y);
    resize(x, y, mousePos);
}
void fui::uiinteractivity::drag(float mouseDX, float mouseDY) {
	if (config.isDraggable && isSelected && isDragging) {
        instance->addPositionInPixels(glm::vec2(mouseDX, mouseDY));
	}
}
void fui::uiinteractivity::resize(float mouseDX, float mouseDY, glm::vec2 mousePos) {
    if (config.isResizeable && isSelected) {
        if (isResizing) {
            if (config.haveOutline)
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
void fui::uiinteractivity::setDragWishPos(glm::vec2 pos, glm::vec2 startPos) {
    //glm::vec2 max = instance->border.max;
    //glm::vec2 t(instance->border.origin.x, instance->border.max.y);
    //instance->addPositionInNDC(glm::vec2(pos.x - instance->border.origin.x, pos.y - instance->border.max.y));
    instance->addPositionInNDC(pos - startPos);
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
    quaterK = instance->border.getQuatersOfBorderContactWithPoint(mousePos, config.distToOutline);
}
void fui::uiinteractivity::addFunctionOnClick(std::function<void(int)> func, int arg) {
    funcsOnClick_int.emplace_back(func, arg);
}
void fui::uiinteractivity::addFunctionOnClick(std::function<void()> func) {
    funcsOnClick_none.push_back(func);
}