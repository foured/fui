#ifndef RECT_HPP
#define RECT_HPP

#include <glm/glm.hpp>

#include "../model2d.h"

std::vector<float> vert = {
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, // top right
     0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   0.0f, 0.0f  // top left 
};

class rect : public fui::model2D {
public:
    std::vector<float> vertices;

	rect(std::vector<float> _vertices = vert)
		: vertices(_vertices), model2D("rect"){ }

	void init() {
        std::vector<unsigned int> indices = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        fui::mesh2D ret(glm::vec3(1.0, 0.0, 0.0));

        ret.setup(fui::vertex::generateVertices(vertices), indices);

        meshes.push_back(ret);
        calcRectBorder2D();
	}
};

#endif // !RECT_HPP
