#include "parent.h"
#include "model2d.h"
#include "fuiscene.h"

fui::parent::parent(transform2D* instance) : instance(instance) {
	border = &instance->border;
	isRoot = false;
}

fui::parent::parent(rectBorder2D* border, bool isRoot) : border(border), isRoot(isRoot) {
	instance = nullptr;
}

void fui::parent::renderChildren(Shader shader, Shader outlineShader) {
	if (children.size() > 0) {
		glEnable(GL_SCISSOR_TEST);
		x = 0;
		y = 0;
		w = scene::width;
		h = scene::height;

		if (instance != nullptr) {
			w *= instance->size.x / 2;
			h *= instance->size.y / 2;
			x = instance->getPositionInPixels().x - w / 2;
			y = instance->getPositionInPixels().y - h / 2;

			int pX = instance->getParent()->x;
			int pY = instance->getParent()->y;
			int pW = instance->getParent()->w;
			int pH = instance->getParent()->h;
			if (x < pX)
				x = pX;
			if (y < pY)
				y = pY;
			if (x + w > pX + pW)
				w = pX + pW - x;
			if (y + h > pY + pH)
				h = pY + pH - y;
		}

		glScissor(x, y, w, h);
		for (transform2D* obj : sim.renderQueue) {
			if (!isVectorContainsValue(sim.outlineQueue, obj)) {
				obj->model->renderInstance_template(shader, obj);
				obj->iAmParent->renderChildren(shader, outlineShader);
			}
		}
		glDisable(GL_SCISSOR_TEST);
		glEnable(GL_SCISSOR_TEST);
		glScissor(x, y, w, h);
		for (transform2D* obj : sim.outlineQueue) {
			obj->model->renderInstance_outline(shader, outlineShader, obj);
			obj->iAmParent->renderChildren(shader, outlineShader);
		}
		sim.outlineQueue.clear();
		addTwoVectors(getRoot()->sim.markerPositions, sim.markerPositions);
		//std::cout << sim.markerPositions.size() << std::endl;

		glDisable(GL_SCISSOR_TEST);
	}
}

void fui::parent::addChild(transform2D* child) {
	children.push_back(child);
	sim.renderQueue.push_back(child);
}

void fui::parent::removeChild(transform2D* child) {
	removeValueFromVector(&children, child);
	removeValueFromVector(&sim.renderQueue, child);
	removeValueFromVector(&sim.outlineQueue, child);
}
bool fui::parent::getIsRoot() {
	return isRoot;
}
fui::parent* fui::parent::getRoot() {
	if (isRoot)
		return this;
	else
		return instance->getParent()->getRoot();
}
