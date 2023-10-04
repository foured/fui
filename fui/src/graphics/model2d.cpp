#include "model2d.h"

fui::model2D::model2D(std::string id)
	: id(id) {}

void fui::model2D::render(Shader shader) {
	shader.activate();
	for (int i = 0, len = meshes.size(); i < len; i++) {
		meshes[i].render();
	}
}

void fui::model2D::calcRectBorder2D() {
	for (int i = 0, len = meshes.size(); i < len; i++) {
		for (int j = 0, len1 = meshes[i].vertices.size(); j < len1; j += 3) {
			float val = meshes[i].vertices[j];
			if (border.min.x > val) border.min.x = val;
			if (border.max.x < val) border.max.x = val;

			val = meshes[i].vertices[j + 1];
			if (border.min.y > val) border.min.y = val;
			if (border.max.y < val) border.max.y = val;
		}
	}
}

void fui::model2D::init(){}