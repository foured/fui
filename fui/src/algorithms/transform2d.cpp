#include "transform2d.h"
#include "../graphics/fuiscene.h"
#include "../graphics/model2d.h"
#include "../graphics/parent.h"

fui::transform2D::transform2D(glm::vec2 pos, glm::vec2 size, glm::vec3 rotation, model2D* model,
	rectBorder2D* modelBoreder, std::string instanceId, parent* parent, uiinteractivity_config config)
	: position(pos), size(size), rotation(rotation), model(model), modelBoreder(modelBoreder), indstanceId(instanceId), orderInLayer(0), 
	myParent(parent), iAmParent(new fui::parent(this)) {
	hasOutline = false;
	myParent->addChild(this);
	calculateBoredr();
	interactivity = uiinteractivity(this, config);
}

fui::transform2D::~transform2D() {

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
	glm::vec2 offset = getPositionInPixels() - posInPix;
	position = glm::vec2(((posInPix.x / (double)fui::scene::width) - 0.5) * 2.0, ((posInPix.y / (double)fui::scene::height) - 0.5) * 2.0);
	calculateBoredr();

	for (transform2D* child : iAmParent->children) {
		child->setPositionInPixels(child->getPositionInPixels() - offset);
	}
}

void fui::transform2D::addPositionInPixels(glm::vec2 offsetInPix) {
	setPositionInPixels(getPositionInPixels() + offsetInPix);
}

void fui::transform2D::setOutline(glm::vec3 color) {
	hasOutline = true;
	outlineColor = color;
}

void fui::transform2D::addPositionInNDC(glm::vec2 offsetInNDC) {
	position += offsetInNDC;
	calculateBoredr();

	for (transform2D* child : iAmParent->children) {
		child->addPositionInNDC(offsetInNDC);
	}
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

	for (transform2D* child : iAmParent->children) {
		if (child->interactivity.config.linkSize) {
			child->changeSizeInPixels(offsetInPix);
		}
	}
}

void fui::transform2D::changeSizeInNDC(glm::vec2 offsetInNDC) {
	glm::vec2 sizeInNDC = size;
	sizeInNDC += offsetInNDC;
	if (sizeInNDC.x > 0.005)
		size = glm::vec2(sizeInNDC.x, size.y);
	if (sizeInNDC.y > 0.005)
		size = glm::vec2(size.x, sizeInNDC.y);
	calculateBoredr();

	for (transform2D* child : iAmParent->children) {
		if (child->interactivity.config.linkSize) {
			child->changeSizeInNDC(offsetInNDC);
		}
	}
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

	for (transform2D* child : iAmParent->children) {
		if (child->interactivity.config.linkSize) {
			child->changeSizeAndGetMultiplier(offsetInPix);
		}
	}

	return multiplier;
}

void fui::transform2D::setParent(transform2D* instance) {
	myParent->removeChild(this);
	instance->iAmParent->addChild(this);
	myParent = instance->iAmParent;
}

void fui::transform2D::setParent(parent* parent) {
	myParent->removeChild(this);
	parent->addChild(this);
	myParent = parent;
}

fui::parent* fui::transform2D::getParent() {
	return myParent;
}