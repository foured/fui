#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#define _USE_MATH_DEFINES
#include <math.h>

#include "../model2d.h"

class circle : public fui::model2D {
public:
	bool hasInitInstances;
	circle() : model2D("circle"), hasInitInstances(false) {}

	void init(int noVertices, glm::vec3 color) {
		float radius = 0.5;
		std::vector<float> vertices;
		for (double i = 0; i < 2 * M_PI; i += 2 * M_PI / noVertices) {
			vertices.push_back(cos(i) * radius);    //X coordinate
			vertices.push_back(sin(i) * radius);    //Y coordinate
			vertices.push_back(0.0);                //Z coordinate
			vertices.push_back(0.0);
			vertices.push_back(0.0);
		}
		std::vector<unsigned int> indices;
		for (int i = 1; i < noVertices; i++) {
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(0);
		}

		fui::mesh2D ret(color);
		ret.setup(fui::vertex::generateVertices(vertices), indices);
		meshes.push_back(ret);
		calcRectBorder2D();
		uiinteractivityConfig = fui::uiinteractivity_config(fui::uiinteractivity_config_type::DISABLE_ALL);
	}
	void renderInstances(Shader shader) {
		if (instances.size() > 0 && !hasInitInstances) {
			initInstances();
			hasInitInstances = true;
		}
		model2D::renderInstances(shader);
	}
};

#endif