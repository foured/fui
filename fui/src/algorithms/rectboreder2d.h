#ifndef RECTBORDER2D_H
#define RECTBORDER2D_H

#include <glm/glm.hpp>

namespace fui {
	class rectBorder2D {
	public:
		glm::vec2 min;
		glm::vec2 max;
		glm::vec2 origin;

		rectBorder2D(glm::vec2 min = glm::vec2(0), glm::vec2 max =  glm::vec2(0));

		bool isDotInRect(glm::vec2 dot);
		bool isRectInRect(rectBorder2D rect);

		double getDistFromPointToBorder(glm::vec2 point);

	private:
		double distance(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2);
		double distance(double x0, double y0, double x1, double y1, double x2, double  y2);
	};
}
#endif // !RECTBORDER2D_H

