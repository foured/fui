#ifndef RECT_HPP
#define RECT_HPP

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

    rect(std::string id, std::vector<float> _vertices = vert)
        : vertices(_vertices), model2D(id) {}

	void init(std::string texturePath) {
        fui::mesh2D ret(fui::texture(texturePath.c_str()));
        registerMeshes(ret);
	}
    void init(glm::vec3 color) {
        fui::mesh2D ret(color);      
        registerMeshes(ret);
    }

private:
    void registerMeshes(fui::mesh2D ret) {
        ret.setup(fui::vertex::generateVertices(vertices), indices);
        meshes.push_back(ret);
        calcRectBorder2D();
        uiinteractivityConfig = fui::uiinteractivity_config();
    }
};

#endif // !RECT_HPP