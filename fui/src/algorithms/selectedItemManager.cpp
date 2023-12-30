#include "selectedItemManager.h"
#include "../graphics/fuiscene.h"

fui::selectedItemAction::selectedItemAction(selectedItemManager* SIM) : type(selectedItemAction_type::FREE), isInAction(false), sim(SIM) {}

bool fui::selectedItemAction::getIsInAction() {
	return isInAction;
}
void fui::selectedItemAction::setAction(fui::selectedItemAction_type actionType, fui::uiinteractivity* interactivity) {
	isInAction = true;
	type = actionType;
	actionObject = interactivity;
}
void fui::selectedItemAction::setDopData(glm::vec2 data, bool boolData) {
	dopData_v2 = data;
	dopData_b = boolData;
}
void fui::selectedItemAction::offAction() {
	if (isInAction) {
		isInAction = false;
		if (haveWP && type == selectedItemAction_type::RESIZING && wpSender->instance->border.
			isPointCloseToBorder(scene::getMousePosInNDC(), wpSender->config.distToOutline) && sim->canBeSelected(wpSender->instance)) {
			actionObject->setResizeWishPos(wishPos);
		}
		else if (haveWP && type == selectedItemAction_type::DRAGGING && wpSender != nullptr){
			if (!dopData_b && wpSender->instance->border.isPointCloseToBorderOutside(scene::getMousePosInNDC(), wpSender->config.distToOutline * 2)
				|| wpSender->instance->border.isPointCloseToBorderOutside(glm::vec2(actionObject->instance->border.max.x, actionObject->instance->border.origin.y), wpSender->config.distToOutline * 2)
				|| wpSender->instance->border.isPointCloseToBorderOutside(glm::vec2(actionObject->instance->border.min.x, actionObject->instance->border.origin.y), wpSender->config.distToOutline * 2)) {
					actionObject->setDragWishPos(wishPos, dopData_v2);
			}
			else if (dopData_b && wpSender->instance->border.isPointCloseToBorder(scene::getMousePosInNDC(), wpSender->config.distToOutline * 2)
				|| wpSender->instance->border.isPointCloseToBorder(glm::vec2(actionObject->instance->border.max.x, actionObject->instance->border.origin.y), wpSender->config.distToOutline * 2)
				|| wpSender->instance->border.isPointCloseToBorder(glm::vec2(actionObject->instance->border.min.x, actionObject->instance->border.origin.y), wpSender->config.distToOutline * 2)) {
				actionObject->setDragWishPos(wishPos, dopData_v2);
			}
		}
		haveWP = false;
	}
}
fui::uiinteractivity* fui::selectedItemAction::getWPSender() {
	return wpSender;
}
fui::uiinteractivity* fui::selectedItemAction::getActionObject() {
	return actionObject;
}
void fui::selectedItemAction::sendWishPos(glm::vec2 wp, fui::uiinteractivity* sender) {
	wishPos = wp;
	haveWP = true;
	wpSender = sender;
	sim->markerPositions.push_back(wp);
}

fui::selectedItemManager::selectedItemManager() : action{this} {
	selectedItem = nullptr;
}
bool fui::selectedItemManager::canBeSelected(transform2D* instance) {
	if (selectedItem == nullptr) return true;

	if (instance == selectedItem) {
		return true;
	}
	else {
		return !selectedItem->border.isDotInRect(scene::getMousePosInNDC());
	}
}
void fui::selectedItemManager::makeMeFirstInOutline(transform2D* model) {
	if (isVectorContainsValue(outlineQueue, model)) {
		removeValueFromVector(&outlineQueue, model);
		outlineQueue.push_back(model);
	}
	else {
		outlineQueue.push_back(model);
	}
}
void fui::selectedItemManager::makeMeFirstInRender(transform2D* model) {
	if (isVectorContainsValue(renderQueue, model)) {
		removeValueFromVector(&renderQueue, model);
		renderQueue.push_back(model);
	}
	else {
		renderQueue.push_back(model);
	}
}
