#include "transform2d.h"
#include "../graphics/fuiscene.h"
#include "../graphics/model2d.h"

fui::transform2D::transform2D(glm::vec2 pos, glm::vec2 size, glm::vec3 rotation, model2D* model, 
	rectBorder2D* modelBoreder, std::string instanceId, uiinteractivity_config config)
	: position(pos), size(size), rotation(rotation), model(model), modelBoreder(modelBoreder), indstanceId(instanceId), orderInLayer(0) {
	calculateBoredr();
	interactivity = uiinteractivity(this, config);
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
	position = glm::vec2(((posInPix.x / (double)fui::scene::width) - 0.5) * 2.0, ((posInPix.y / (double)fui::scene::height) - 0.5) * 2.0);
	calculateBoredr();
}

void fui::transform2D::addPositionInPixels(glm::vec2 offsetInPix) {
	setPositionInPixels(getPositionInPixels() + offsetInPix);
}

void fui::transform2D::addPositionInNDC(glm::vec2 offsetInNDC) {
	position += offsetInNDC;
	calculateBoredr();
}

void fui::transform2D::calculateBoredr() {
	border = rectBorder2D(modelBoreder->min * size + position, modelBoreder->max * size + position);
}

void fui::transform2D::changeSizeInPixels(glm::vec2 offsetInPix) {
	glm::vec2 sizeInPix = getSizeInPixels();
	sizeInPix += offsetInPix;
	sizeInPix = glm::vec2(sizeInPix.x / (double)fui::scene::width, sizeInPix.y / (double)fui::scene::height);
	if (sizeInPix.x > 0.005)
		size = glm::vec2(sizeInPix.x, size.y);
	if (sizeInPix.y > 0.005)
		size = glm::vec2(size.x, sizeInPix.y);
	calculateBoredr();
}

void fui::transform2D::changeSizeInNDC(glm::vec2 offsetInNDC) {
	glm::vec2 sizeInNDC = size;
	sizeInNDC += offsetInNDC;
	if (sizeInNDC.x > 0.005)
		size = glm::vec2(sizeInNDC.x, size.y);
	if (sizeInNDC.y > 0.005)
		size = glm::vec2(size.x, sizeInNDC.y);
	calculateBoredr();
}

glm::vec2 fui::transform2D::changeSizeAndGetMultiplier(glm::vec2 offsetInPix) {
	glm::vec2 multiplier = glm::vec2(1.0);
	glm::vec2 sizeInPix = getSizeInPixels();
	sizeInPix += offsetInPix;
	sizeInPix = glm::vec2(sizeInPix.x / (double)fui::scene::width, sizeInPix.y / (double)fui::scene::height);
	if (sizeInPix.x > 0.005)
		size = glm::vec2(sizeInPix.x, size.y);
	else
		multiplier = glm::vec2(0.0, multiplier.y);

	if (sizeInPix.y > 0.005)
		size = glm::vec2(size.x, sizeInPix.y);
	else
		multiplier = glm::vec2(multiplier.x, 0.0);

	calculateBoredr();
	return multiplier;
}