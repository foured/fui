#ifndef RECT_HPP
#define RECT_HPP

#include "../model2d.h"

class rect : public fui::model2D {
public:
	rect()
		: model2D("rect"){ }

	void init() {
        std::vector<float> vertices = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
        };
        std::vector<unsigned int> indices = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        fui::mesh2D ret;

        ret.setup(vertices, indices);

        meshes.push_back(ret);
        calcRectBorder2D();
	}
};

#endif // !RECT_HPP
