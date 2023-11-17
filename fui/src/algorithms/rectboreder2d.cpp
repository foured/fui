#include "rectboreder2d.h"

#include <cmath>

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


double fui::rectBorder2D::getDistFromPointToBorder(glm::vec2 point) {
	if (point.x < origin.x && point.y < origin.y) {
		if (abs(point.x - min.x) < abs(point.y - min.y)) {
			return distance(point, min, glm::vec2(max.x, min.y));
		}
		else {
			return distance(point, min, glm::vec2(min.x, max.y));
		}
	}
	else if (point.x > origin.x && point.y < origin.y) {
		if (abs(point.x - min.x) < abs(point.y - min.y)) {
			return distance(point, max, glm::vec2(min.x, max.y));
		}
		else {
			return distance(point, min, glm::vec2(min.x, max.y));
		}
	}
	else if (point.x > origin.x && point.y > origin.y) {
		if (abs(point.x - min.x) < abs(point.y - min.y)) {
			return distance(point, max, glm::vec2(min.x, max.y));
		}
		else {
			return distance(point, max, glm::vec2(max.x, min.y));
		}
	}
	else {
		if (abs(point.x - min.x) < abs(point.y - min.y)) {
			return distance(point, min, glm::vec2(max.x, min.y));
		}
		else {
			return distance(point, max, glm::vec2(max.x, min.y));
		}
	}
}

double fui::rectBorder2D::distance(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2) {
	return distance(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y);
}

double fui::rectBorder2D::distance(double x0, double y0, double x1, double y1, double x2, double  y2) {
	return abs((y2 - y1) * x0 - (x2 - x1) * y0 + x2 * y1 - y2 * x1) / sqrt(pow(y2 - y1, 2.0) + pow(x2 - x1, 2.0));
}