#ifndef OUTLINE_H
#define OUTLINE_H

#include "mesh2d.h"

namespace fui {
	class outline {
	public:
		std::vector<mesh2D> meshes;

		void initOutline(std::vector<mesh2D> nMeshes);
		void renderInstance(Shader shader, glm::vec2 position, glm::vec2 size, glm::vec3  color);

	private:
		unsigned int noInstances;
		BufferObject posVBO, sizeVBO;
	};
}

#endif