#include "transform2d.h"

fui::transform2D::transform2D(glm::vec2 pos, glm::vec2 size, glm::vec3 rotation, model2D* model)
	: position(pos), size(size), rotation(rotation), model(model) {}

glm::vec2 fui::transform2D::getPositionInPixels() {
	return glm::vec2(position.x * fui::scene::width, position.y * fui::scene::height);
}

glm::vec2 fui::transform2D::getSizeInPixels() {
	return glm::vec2(size.x * fui::scene::width, size.y * fui::scene::height);
}

void fui::transform2D::setPositionInPixels(glm::vec2 posInPix) {
	position = glm::vec2(posInPix.x / fui::scene::width, posInPix.y / fui::scene::height);
}