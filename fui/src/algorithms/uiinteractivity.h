#ifndef UIINTERACTIVITY_H
#define UIINTERACTIVITY_H

#include <vector>
#include <functional>

#include "../graphics/shader.h"
#include "../io/mouse.h"

namespace fui {
	class transform2D;
	class selectedItemManager;
	class uiinteractivity {
	public:
		transform2D *instance;

		uiinteractivity();
		uiinteractivity(transform2D* transform);

		bool isDraggable;
		bool isResizeable;
		bool isSelected;

		double distToOutline;

		void update();
		void drag(float mouseDX, float mouseDY);
		void resize(float mouseDX, float mouseDY, glm::vec2 mousePos);
		void click();

		void setSIM(selectedItemManager* SIM);
		void setResizeWishPos(glm::vec2 pos);

		void addFunctionOnClick(std::function<void()> func);
		void addFunctionOnClick(std::function<void(int)> func, int arg);

	private:
		selectedItemManager* sim;
		bool isResizing;
		int xk, yk;
		glm::vec2 quaterK;
		void calculateResize(glm::vec2 mousePos);

		std::vector<std::function<void()>> funcsOnClick_none;
		std::vector<std::pair<std::function<void(int)>, int>> funcsOnClick_int;
	};
}

#endif