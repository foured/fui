#ifndef PARENT_H
#define PARENT_H

#include <vector>
#include "../algorithms/selectedItemManager.h"

namespace fui {
	class selectedItemManager;

	class parent {
	public:
		selectedItemManager sim;
		transform2D* instance;
		std::vector<transform2D*> children;

		parent(transform2D* instance);
		parent(rectBorder2D* border);
		void addChild(transform2D* child);
		void removeChild(transform2D* child);
		void renderChildren(Shader shader, Shader outlineShader);

	private:
		rectBorder2D* border;
	};
}
#endif // !PARENT_H
