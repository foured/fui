#include "uiinteractivity.h"
#include "transform2d.h"

fui::uiinteractivity::uiinteractivity(){}

fui::uiinteractivity::uiinteractivity(transform2D* transform) 
    : instance(transform) {
	isDraggable = true;
	isResizeable = true;
    distToOutline = 0.02;
}

void fui::uiinteractivity::update(Shader outlineShader) {
    drag(outlineShader);
}

void fui::uiinteractivity::drag(Shader outlineShader) {
	if (isDraggable) {
        if (instance->border.isDotInRect(fui::scene::getMousePosInNDC())) {
            float x = Mouse::getDX();
            float y = Mouse::getDY();
            if (instance->border.isPointCloseToBorder(fui::scene::getMousePosInNDC(), distToOutline))
                instance->model->addToShadersQueue(outlineShader, instance->model->getInstaneIdxById(instance->indstanceId));
            instance->addPositionInPixels(glm::vec2(x, y));
        }
	}
}