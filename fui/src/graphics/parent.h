#ifndef PARENT_H
#define PARENT_H

#include <vector>

#include "../algorithms/transform2d.h"
#include "../algorithms/rectboreder2d.h"
#include "../algorithms/selectedItemManager.h"

namespace fui {
	class parent {
	public:
		std::vector<transform2D*> children;

		parent(rectBorder2D* border);
		void addChild(transform2D* child);
		void renderChildren(Shader shader, Shader outlineShader);

	private:
		rectBorder2D* border;
		selectedItemManager sim;
	};
}

#endif // !PARENT_H
