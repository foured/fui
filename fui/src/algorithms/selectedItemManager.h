#ifndef SELECTEDITEMMANAGER_H
#define SELECTEDITEMMANAGER_H

#include "transform2d.h"
#include "fuifunctions.hpp"

namespace fui {
	class transform2d;
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
		void setDopData(glm::vec2 data);
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
		glm::vec2 dopData;
	};

	class selectedItemManager {
	public:
		selectedItemManager();
		transform2D* selectedItem;
		std::vector<model2D*> outlineQueue;
		std::vector<model2D*> renderQueue;
		std::vector<glm::vec2> markerPositions;

		selectedItemAction action;

		void makeMeFirstInOutline(model2D* model);
		void makeMeFirstInRender(model2D* model);
		bool canBeSelected(transform2D* instance);

	private:
	};
}

#endif