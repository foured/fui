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

std::vector<unsigned int> outlineIndices = {
    0, 1, 7,
    6, 7, 0,
    2, 3, 0,
    0, 1, 3,
    2, 3, 4,
    5, 4, 3,
    4, 5, 7,
    6, 7, 4
};

std::vector<float> outlineVert = {
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, // top right
     0.51f,  0.51f, 0.0f,   0.0f, 0.0f, // top top right

     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, // bottom right
     0.51f, -0.51f, 0.0f,   0.0f, 1.0f, // bottom bottom right

    -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, // bottom left
    -0.51f, -0.51f, 0.0f,   1.0f, 1.0f, // bottom bottom left

    -0.5f,  0.5f, 0.0f,   1.0f, 0.0f,  // top left 
    -0.51f,  0.51f, 0.0f,   1.0f, 0.0f  // top top left 
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

        fui::mesh2D oMesh;
        oMesh.setup(fui::vertex::generateVertices(outlineVert), outlineIndices);
        std::vector<fui::mesh2D> oMeshes;
        oMeshes.push_back(oMesh);
        modelOutline.initOutline(oMeshes);
    }
};

#endif // !RECT_HPP