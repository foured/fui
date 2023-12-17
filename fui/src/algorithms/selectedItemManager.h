#ifndef SELECTEDITEMMANAGER_H
#define SELECTEDITEMMANAGER_H

#include "transform2d.h"
#include "fuifunctions.hpp"

namespace fui {
	class transform2d;
	class model2d;

	class selectedItemManager {
	public:
		selectedItemManager();
		transform2D* selectedItem;
		std::vector<model2D*> outlineQueue;
		std::vector<model2D*> renderQueue;

		void setResizing(uiinteractivity* interactivity);
		void offResizing();
		bool getResizing();
		uiinteractivity* getWPSender();
		uiinteractivity* getResisingObject();
		void sendWishPos(glm::vec2 wp, uiinteractivity* sebder);
		void clearWishPos();
		void makeMeFirstInOutline(model2D* model);
		void makeMeFirstInRender(model2D* model);
		bool canBeSelected(transform2D* instance);

	private:
		bool haveWP;
		bool isResizing;
		uiinteractivity* resizedObject;
		uiinteractivity* wpSender;
		glm::vec2 wishPos;
	};
}

#endif