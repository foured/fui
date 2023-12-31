#include "uiinteractivity.h"
#include "transform2d.h"
#include "../graphics/fuiscene.h"
#include "../graphics/parent.h"


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
    linkSize.x = false;
    linkSize.y = false;
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
    selectedItemManager* pSim = &instance->iAmParent->sim;
    if (scene::mouseButtonWentDown(GLFW_MOUSE_BUTTON_1) && instance->border.isDotInRect(mousePos) && getsim()->canBeSelected(instance)) {
        getsim()->selectedItem = instance;
        getsim()->makeMeFirstInRender(instance);
        instance->orderInLayer = 1;

        isSelected = true;
        if (instance->border.isPointCloseToBorder(mousePos, config.distToOutline)
            && instance->border.getQuatersOfBorderContactWithPoint(mousePos, config.distToOutline) != glm::vec2(0, 1)) {
            isResizing = true;
            calculateResize(mousePos);
            getsim()->action.setAction(selectedItemAction_type::RESIZING, this);
        }
        else if (instance->border.isPointCloseToBorder(mousePos, config.distToOutline)) {
            isDragging = true;
            getsim()->action.setAction(selectedItemAction_type::DRAGGING, this);
        }
        click();
    }
    else if (instance->border.isPointCloseToBorder(mousePos, config.distToOutline) && getsim()->canBeSelected(instance)) {
        if (getsim()->action.getIsInAction() && getsim()->action.type == selectedItemAction_type::RESIZING && getsim()->action.getActionObject() != this) {
            getsim()->action.sendWishPos(instance->border.getCoordOfContactBorder(mousePos, config.distToOutline), this);
        }
        else {
            if (config.haveOutline)
                instance->setOutline(glm::vec3(0.01, 0.42, 0.17));
            getsim()->makeMeFirstInOutline(instance);
        }
    }
    else if(getsim()->action.getIsInAction() && getsim()->action.type == selectedItemAction_type::DRAGGING && getsim()->action.getActionObject() != this){
        transform2D* aInstance = getsim()->action.getActionObject()->instance;

        if (instance->border.isPointCloseToBorderOutside(mousePos, config.distToOutline * 2)) { //top
            glm::vec2 contact = instance->border.getCoordOfContactBorderOutSide(mousePos, config.distToOutline * 2);
            getsim()->action.sendWishPos(contact, this);
            getsim()->action.setDopData(glm::vec2(contact.x, aInstance->border.max.y));
        }
        else if (instance->border.isPointCloseToBorderOutside(glm::vec2(aInstance->border.max.x, aInstance->border.origin.y), config.distToOutline * 2)) { //right
            glm::vec2 contact = instance->border.getCoordOfContactBorderOutSide(glm::vec2(aInstance->border.max.x, aInstance->border.origin.y), config.distToOutline * 2);
            getsim()->action.sendWishPos(contact, this);
            getsim()->action.setDopData(glm::vec2(aInstance->border.max.x, contact.y));
        }
        else if (instance->border.isPointCloseToBorderOutside(glm::vec2(aInstance->border.min.x, aInstance->border.origin.y), config.distToOutline * 2)) { //left
            glm::vec2 contact = instance->border.getCoordOfContactBorderOutSide(glm::vec2(aInstance->border.min.x, aInstance->border.origin.y), config.distToOutline * 2);
            getsim()->action.sendWishPos(contact, this);
            getsim()->action.setDopData(glm::vec2(aInstance->border.min.x, contact.y));
        }
    }
    //else if (pSim->action.getIsInAction() && pSim->action.type == selectedItemAction_type::DRAGGING && pSim->action.getActionObject() != this) {
    //    transform2D* aInstance = pSim->action.getActionObject()->instance;
    //    if (instance->border.isPointCloseToBorder(mousePos, config.distToOutline * 2)) { //top
    //        glm::vec2 contact = instance->border.getCoordOfContactBorder(mousePos, config.distToOutline * 2);
    //        pSim->action.sendWishPos(contact, this);
    //        pSim->action.setDopData(glm::vec2(contact.x, aInstance->border.max.y), true);
    //    }
    //    else if (instance->border.isPointCloseToBorder(glm::vec2(aInstance->border.max.x, aInstance->border.origin.y), config.distToOutline * 2)) { //right
    //        glm::vec2 contact = instance->border.getCoordOfContactBorder(glm::vec2(aInstance->border.max.x, aInstance->border.origin.y), config.distToOutline * 2);
    //        pSim->action.sendWishPos(contact, this);
    //        pSim->action.setDopData(glm::vec2(aInstance->border.max.x, contact.y), true);
    //    }
    //    else if (instance->border.isPointCloseToBorder(glm::vec2(aInstance->border.min.x, aInstance->border.origin.y), config.distToOutline * 2)) { //left
    //        glm::vec2 contact = instance->border.getCoordOfContactBorder(glm::vec2(aInstance->border.min.x, aInstance->border.origin.y), config.distToOutline * 2);
    //        pSim->action.sendWishPos(contact, this);
    //        pSim->action.setDopData(glm::vec2(aInstance->border.min.x, contact.y), true);
    //    }
    //}

    if (scene::mouseButtonWentUp(GLFW_MOUSE_BUTTON_1)) {
        if (getsim()->selectedItem == instance) {
            instance->orderInLayer = 0;
            getsim()->action.offAction();
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
                instance->setOutline(glm::vec3(0.0, 0.8, 0.1));
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
    instance->addPositionInNDC(pos - startPos);
}

fui::selectedItemManager* fui::uiinteractivity::getsim() {
    return &instance->getParent()->sim;
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
    quaterK = instance->border.getQuatersOfBorderContactWithPoint(mousePos, config.distToOutline);
}

void fui::uiinteractivity::addFunctionOnClick(std::function<void(int)> func, int arg) {
    funcsOnClick_int.emplace_back(func, arg);
}

void fui::uiinteractivity::addFunctionOnClick(std::function<void()> func) {
    funcsOnClick_none.push_back(func);
}