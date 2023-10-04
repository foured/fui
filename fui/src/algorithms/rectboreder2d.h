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
	};
}
#endif // !RECTBORDER2D_H

