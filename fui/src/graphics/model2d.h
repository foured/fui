#ifndef MODEL2D_H
#define MODEL2D_H

#include <string>
#include <vector>

#include "mesh2d.h"
#include "shader.h"

#include "../algorithms/rectboreder2d.h"
#include "../algorithms/transform2d.h"

namespace fui {
	class transform2D;

	class model2D {
	public:
		std::vector<mesh2D> meshes;
		std::string id;

		std::vector<transform2D*> instances;

		model2D(std::string id);

		void init();
		void renderInstances(Shader shader);
		void calcRectBorder2D();
		void generateInstance(glm::vec2 pos, glm::vec2 size = glm::vec2(1.0), glm::vec3 rotation = glm::vec3(0.0));
		void initInstances();
		rectBorder2D getInstanseBorder(unsigned int instanceIdx);

	private:
		BufferObject posVBO, sizeVBO;
		rectBorder2D border;
	};
}

#endif // !MODEL2D_H
