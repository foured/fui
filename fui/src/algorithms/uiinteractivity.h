#ifndef UIINTERACTIVITY_H
#define UIINTERACTIVITY_H

#include "../graphics/shader.h"
#include "../graphics/fuiscene.h"

namespace fui {
	class transform2D;

	class uiinteractivity {
	public:
		transform2D *instance;

		uiinteractivity();
		uiinteractivity(transform2D* transform);

		bool isDraggable;
		bool isResizeable;

		double distToOutline;

		void update(Shader outlineShader);
		void drag(Shader outlineShader);
	};
}

#endif