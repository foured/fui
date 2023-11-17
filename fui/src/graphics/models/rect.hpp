#ifndef RECT_HPP
#define RECT_HPP

#include <glm/glm.hpp>

#include "../model2d.h"

std::vector<unsigned int> indices = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

std::vector<float> vert = {
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 0.0f  // top left 
};

class rect : public fui::model2D {
public:
    std::vector<float> vertices;

    rect(fui::scene scene, std::vector<float> _vertices = vert)
		: vertices(_vertices), model2D("rect", scene){ }

	void init() {
        //fui::mesh2D ret(glm::vec3(1.0, 0.0, 0.0));      
        fui::mesh2D ret(fui::texture("assets/textures/alice.jpg"));

        ret.setup(fui::vertex::generateVertices(vertices), indices);

        meshes.push_back(ret);
        calcRectBorder2D();
	}
};

#endif // !RECT_HPP