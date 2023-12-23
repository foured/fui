#include "parent.h"

fui::parent::parent(rectBorder2D* border) : border(border) {}

void fui::parent::renderChildren(Shader shader, Shader outlineShader) {
	glScissor(border->min.x, border->min.y, border->max.x - border->min.x, border->max.y - border->min.y);

	for (transform2D* child : children) {

	}
}
void fui::parent::addChild(transform2D* child) {
	child->interactivity.setSIM(&sim);
	children.push_back(child);
}