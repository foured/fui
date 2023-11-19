#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include <string>

#include <glm/glm.hpp>

#include "../graphics/fuiscene.h"
#include "../graphics/model2d.h"

#include "uiinteractivity.h"
#include "rectboreder2d.h"

namespace fui {
	class model2D;

	class transform2D {
	public:
		glm::vec2 position;
		glm::vec2 size;
		glm::vec3 rotation;

		rectBorder2D border;
		uiinteractivity interactivity;

		model2D* model;
		std::string indstanceId;

		transform2D(glm::vec2 pos, glm::vec2 size, glm::vec3 rotation, model2D* model, rectBorder2D* modelBoreder, std::string instanceId);

		glm::vec2 getPositionInPixels();
		glm::vec2 getSizeInPixels();

		void setPositionInPixels(glm::vec2 posInPix);
		void addPositionInPixels(glm::vec2 offsetInPix);
		void changeSize(glm::vec2 offsetInPix);
		glm::vec2 changeSizeAndGetMultiplier(glm::vec2 offsetInPix);

	private:
		rectBorder2D* modelBoreder;
		void calculateBoredr();
	};
}

#endif // !TRANSFORM2D_H
