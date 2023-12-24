#include "parent.h"
#include "model2d.h"
#include "fuiscene.h"

fui::parent::parent(transform2D* instance) : instance(instance) {
	border = &instance->border;
}

fui::parent::parent(rectBorder2D* border) : border(border) {
	instance = nullptr;
}

void fui::parent::renderChildren(Shader shader, Shader outlineShader) {
	if (children.size() > 0) {
		glEnable(GL_SCISSOR_TEST);
		int x = 0;
		int y = 0;
		int w = scene::width;
		int h = scene::height;

		if (instance != nullptr) {
			w *= instance->size.x / 2;
			h *= instance->size.y / 2;
			x = instance->getPositionInPixels().x - w / 2;
			y = instance->getPositionInPixels().y - h / 2;
		}

		glScissor(x, y, w, h);

		for (transform2D* obj : sim.renderQueue) {
			obj->model->renderInstance_template(shader, obj);
			obj->iAmParent->renderChildren(shader, outlineShader);
		}
		for (transform2D* obj : sim.outlineQueue) {
			obj->model->renderInstance_outline(shader, outlineShader, obj);
			obj->iAmParent->renderChildren(shader, outlineShader);
		}
		sim.outlineQueue.clear();

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