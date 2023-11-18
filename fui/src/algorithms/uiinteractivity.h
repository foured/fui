#ifndef UIINTERACTIVITY_H
#define UIINTERACTIVITY_H

#include "../graphics/shader.h"
#include "../graphics/fuiscene.h"

#include "../io/mouse.h"

namespace fui {
	class transform2D;

	class uiinteractivity {
	public:
		transform2D *instance;

		uiinteractivity();
		uiinteractivity(transform2D* transform);

		bool isDraggable;
		bool isResizeable;
		bool isSelected;

		double distToOutline;

		void update(Shader outlineShader);
		void drag(float mouseDX, float mouseDY);
		void resize(Shader outlineShader, float mouseDX, float mouseDY, glm::vec2 mousePos);

	private:
		bool isResizing;
		int xk, yk;
		glm::vec2 quaterK;
		void calculateResize(glm::vec2 mousePos);
	};
}

#endif