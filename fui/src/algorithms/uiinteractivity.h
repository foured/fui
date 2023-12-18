#ifndef UIINTERACTIVITY_H
#define UIINTERACTIVITY_H

#include <vector>
#include <functional>

#include "../graphics/shader.h"
#include "../io/mouse.h"

namespace fui {
	class transform2D;
	class selectedItemManager;
	class selectedItemAction;
	enum selectedItemAction_type;

	enum uiinteractivity_config_type : char {
		ACTIVE_ALL,
		DISABLE_ALL,
		CUSTOM
	};

	class uiinteractivity_config {
	public:
		uiinteractivity_config(uiinteractivity_config_type type = uiinteractivity_config_type::ACTIVE_ALL);

		bool isDraggable;
		bool isResizeable;
		bool haveOutline;

		double distToOutline;
	};

	class uiinteractivity {
	public:
		transform2D *instance;

		uiinteractivity();
		uiinteractivity(transform2D* transform, uiinteractivity_config config = uiinteractivity_config(uiinteractivity_config_type::ACTIVE_ALL));

		uiinteractivity_config config;
		bool isSelected;

		void update();
		void drag(float mouseDX, float mouseDY);
		void resize(float mouseDX, float mouseDY, glm::vec2 mousePos);
		void click();

		void setSIM(selectedItemManager* SIM);
		void setResizeWishPos(glm::vec2 pos);
		void setDragWishPos(glm::vec2 pos, glm::vec2 startPos);

		void addFunctionOnClick(std::function<void()> func);
		void addFunctionOnClick(std::function<void(int)> func, int arg);

	private:
		bool isResizing;
		bool isDragging;

		selectedItemManager* sim;

		int xk, yk;
		glm::vec2 quaterK;
		void calculateResize(glm::vec2 mousePos);

		std::vector<std::function<void()>> funcsOnClick_none;
		std::vector<std::pair<std::function<void(int)>, int>> funcsOnClick_int;
	};
}

#endif