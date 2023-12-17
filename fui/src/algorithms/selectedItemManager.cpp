#include "selectedItemManager.h"
#include "../graphics/fuiscene.h"

fui::selectedItemAction::selectedItemAction(selectedItemManager* SIM) : type(selectedItemAction_type::FREE), isInAction(false), sim(SIM) {}

bool fui::selectedItemAction::getIsInAction() {
	return isInAction;
}
void fui::selectedItemAction::setAction(fui::selectedItemAction_type actionType, fui::uiinteractivity* interactivity) {
	isInAction = true;
	type = actionType;
	haveWP = false;
	actionObject = interactivity;
}
void fui::selectedItemAction::offAction() {
	isInAction = false;
	if (haveWP && wpSender->instance->border.isPointCloseToBorder(scene::getMousePosInNDC(), wpSender->config.distToOutline)
		&& sim->canBeSelected(wpSender->instance)) {
		
		if (type == selectedItemAction_type::RESIZING)
			actionObject->setResizeWishPos(wishPos);
	}
	haveWP = false;
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
	isResizing = false;
	haveWP = false;
	wpSender = nullptr;

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
void fui::selectedItemManager::setResizing(uiinteractivity* interactivity) {
	isResizing = true;
	haveWP = false;
	resizedObject = interactivity;
}
void fui::selectedItemManager::offResizing() {
	isResizing = false;
	if (haveWP && wpSender->instance->border.isPointCloseToBorder(scene::getMousePosInNDC(), wpSender->config.distToOutline) 
		&& canBeSelected(wpSender->instance)) {
		resizedObject->setResizeWishPos(wishPos);
	}
	haveWP = false;
}
bool fui::selectedItemManager::getResizing() {
	return isResizing;
}
fui::uiinteractivity* fui::selectedItemManager::getWPSender() {
	return wpSender;
}
fui::uiinteractivity* fui::selectedItemManager::getResisingObject() {
	return resizedObject;
}
void fui::selectedItemManager::sendWishPos(glm::vec2 wp, uiinteractivity* sender) {
	wishPos = wp;
	haveWP = true;
	wpSender = sender;
	markerPositions.push_back(wp);
}
void fui::selectedItemManager::makeMeFirstInOutline(model2D* model) {
	if (isVectorContainsValue(outlineQueue, model)) {
		removeValueFromVector(&outlineQueue, model);
		outlineQueue.push_back(model);
	}
	else {
		outlineQueue.push_back(model);
	}
}
void fui::selectedItemManager::makeMeFirstInRender(model2D* model) {
	if (isVectorContainsValue(renderQueue, model)) {
		removeValueFromVector(&renderQueue, model);
		renderQueue.push_back(model);
	}
	else {
		renderQueue.push_back(model);
	}
}
