#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include <string>

#include <glm/glm.hpp>

#include "uiinteractivity.h"
#include "rectboreder2d.h"

namespace fui {
	class model2D;
	class parent;

	class transform2D {
	public:
		glm::vec2 position;
		glm::vec2 size;
		glm::vec3 rotation;

		int orderInLayer;
		bool hasOutline;
		glm::vec3 outlineColor;

		rectBorder2D border;
		uiinteractivity interactivity;

		parent* iAmParent;

		model2D* model;
		std::string indstanceId;

		transform2D(glm::vec2 pos, glm::vec2 size, glm::vec3 rotation, model2D* model, 
			rectBorder2D* modelBoreder, std::string instanceId, parent* parent, uiinteractivity_config config);
		~transform2D();

		void setOutline(glm::vec3 color);
		void setParent(transform2D* instance);
		void setParent(parent* parent);
		parent* getParent();

		glm::vec2 getPositionInPixels();
		glm::vec2 getSizeInPixels();

		void setPositionInPixels(glm::vec2 posInPix);
		void addPositionInPixels(glm::vec2 offsetInPix);
		void addPositionInNDC(glm::vec2 offsetInNDC);
		void changeSizeInPixels(glm::vec2 offsetInPix);
		void changeSizeInNDC(glm::vec2 offsetInNDC);
		glm::vec2 changeSizeAndGetMultiplier(glm::vec2 offsetInPix);

	private:
		rectBorder2D* modelBoreder;
		parent* myParent;
		void calculateBoredr();
	};
}

#endif // !TRANSFORM2D_H
