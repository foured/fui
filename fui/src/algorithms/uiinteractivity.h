#ifndef UIINTERACTIVITY_H
#define UIINTERACTIVITY_H

#include "../graphics/shader.h"
#include "../graphics/fuiscene.h"

#include "transform2d.h"

namespace fui {
	class transform2D;

	class uiinteractivity {
	public:
		transform2D *instance;

		uiinteractivity(transform2D* transform, scene scene);

		bool isDraggable;
		bool isResizeable;

		void update(Shader outlineShader);
		void drag(Shader outlineShader);

		scene scene;
	};
}

#endif