#include "uiinteractivity.h"

fui::uiinteractivity::uiinteractivity(transform2D* transform, fui::scene scene) 
    : scene(scene), instance(transform) {
	isDraggable = true;
	isResizeable = true;
}

void fui::uiinteractivity::update(Shader outlineShader) {
    drag(outlineShader);
}

void fui::uiinteractivity::drag(Shader outlineShader) {
	if (isDraggable) {
        if (instance->border.isDotInRect(scene.getMousePosInNDC())) {
            float x = Mouse::getDX();
            float y = Mouse::getDY();
            if (instance->border.getDistFromPointToBorder(scene.getMousePosInNDC()) < 0.2)
                instance->model->addToShadersQueue(outlineShader, instance->model->getInstaneIdxById(instance->indstanceId));
            instance->addPositionInPixels(glm::vec2(x, y));
        }
	}
}