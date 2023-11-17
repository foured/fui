#include "transform2d.h"

fui::transform2D::transform2D(glm::vec2 pos, glm::vec2 size, glm::vec3 rotation, model2D* model, rectBorder2D* modelBoreder, std::string instanceId)
	: position(pos), size(size), rotation(rotation), model(model), modelBoreder(modelBoreder), indstanceId(instanceId) {
	calculateBoredr();
	interactivity = uiinteractivity(this, model->scene);
}

glm::vec2 fui::transform2D::getPositionInPixels() {
	float x = (position.x + 1) / 2;
	float y = (position.y + 1) / 2;
	return glm::vec2(x * fui::scene::width, y * fui::scene::height);
}

glm::vec2 fui::transform2D::getSizeInPixels() {
	return glm::vec2(size.x * fui::scene::width, size.y * fui::scene::height);
}

void fui::transform2D::setPositionInPixels(glm::vec2 posInPix) {
	position = glm::vec2(((posInPix.x / (double)fui::scene::width) - 0.5) * 2, ((posInPix.y / (double)fui::scene::height) - 0.5) * 2);
	calculateBoredr();
}

void fui::transform2D::addPositionInPixels(glm::vec2 offsetInPix) {
	setPositionInPixels(getPositionInPixels() + offsetInPix);
}

void fui::transform2D::calculateBoredr() {
	border = rectBorder2D(modelBoreder->min * size + position, modelBoreder->max * size + position);
}