#ifndef MARKER_H
#define MARKER_H

#include <string>
#include <vector>

#include "mesh2d.h"
#include "shader.h"

namespace fui {
	class marker {
	public:
		std::vector<mesh2D> meshes;
		glm::vec3 color;

		marker(glm::vec3 color);
		
		void init();
		void render(Shader shader, std::vector<glm::vec2> positions);
		void cleanup();

	private:
		BufferObject posVBO, sizeVBO;
		glm::vec3 size;
	};
}

#endif