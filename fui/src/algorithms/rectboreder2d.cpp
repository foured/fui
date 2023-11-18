#include "rectboreder2d.h"

#include <cmath>

fui::rectBorder2D::rectBorder2D(glm::vec2 min, glm::vec2 max) 
	: min(min), max(max) {
	calculateOrigin();
}

bool fui::rectBorder2D::isDotInRect(glm::vec2 dot) {
	return (dot.x > min.x && dot.x < max.x) && (dot.y > min.y && dot.y < max.y);
}
bool fui::rectBorder2D::isRectInRect(rectBorder2D rect) {
	if (max.x < rect.min.x || min.x > rect.max.x) return false;
	if (max.y < rect.min.y || min.y > rect.max.y) return false;

	return true;
}
void fui::rectBorder2D::calculateOrigin() {
	origin = glm::vec2((min.x + max.x) / 2, (min.y + max.y) / 2);
}
bool fui::rectBorder2D::isPointCloseToBorder(glm::vec2 point, double distToBorder){
	bool res = false;

	res  = res || rectBorder2D(min, glm::vec2(max.x, min.y + distToBorder)).isDotInRect(point); // down
	res  = res || rectBorder2D(glm::vec2(min.x, max.y - distToBorder), max).isDotInRect(point); // top
	res  = res || rectBorder2D(min, glm::vec2(min.x + distToBorder, max.y)).isDotInRect(point); // left
	res  = res || rectBorder2D(glm::vec2(max.x - distToBorder, min.y), max).isDotInRect(point); // right

	return res;
}