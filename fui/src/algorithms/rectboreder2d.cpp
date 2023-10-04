#include "rectboreder2d.h"

fui::rectBorder2D::rectBorder2D(glm::vec2 min, glm::vec2 max) 
	: min(min), max(max) {
	origin = glm::vec2((max.x - min.x) / 2, (max.y - min.y) / 2);
}

bool fui::rectBorder2D::isDotInRect(glm::vec2 dot) {
	return (dot.x > min.x && dot.x < max.x) && (dot.y > min.y && dot.y < max.y);
}
bool fui::rectBorder2D::isRectInRect(rectBorder2D rect) {
	if (max.x < rect.min.x || min.x > rect.max.x) return false;
	if (max.y < rect.min.y || min.y > rect.max.y) return false;

	return true;
}