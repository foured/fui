#ifndef SELECTEDITEMMANAGER_H
#define SELECTEDITEMMANAGER_H

#include "transform2d.h"
#include "fuifunctions.hpp"

namespace fui {
	class model2d;
	enum selectedItemAction_type : char {
		FREE,
		RESIZING,
		DRAGGING
	};

	class selectedItemAction {
	public:
		selectedItemAction(selectedItemManager* SIM);

		selectedItemAction_type type;
		bool getIsInAction();
		void setAction(selectedItemAction_type type, uiinteractivity* interactivity);
		void setDopData(glm::vec2 data, bool boolData = false);
		void offAction();
		uiinteractivity* getWPSender();
		uiinteractivity* getActionObject();
		void sendWishPos(glm::vec2 wp, uiinteractivity* sender);

	private:
		selectedItemManager* sim;
		bool isInAction;
		bool haveWP;
		uiinteractivity* actionObject;
		uiinteractivity* wpSender;
		glm::vec2 wishPos;
		glm::vec2 dopData_v2;
		bool dopData_b;
	};

	class selectedItemManager {
	public:
		selectedItemManager();
		transform2D* selectedItem;
		std::vector<transform2D*> outlineQueue;
		std::vector<transform2D*> renderQueue;
		std::vector<glm::vec2> markerPositions;

		selectedItemAction action;

		void makeMeFirstInOutline(transform2D* model);
		void makeMeFirstInRender(transform2D* model);
		bool canBeSelected(transform2D* instance);
	};
}

#endif