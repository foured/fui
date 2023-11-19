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
	class uiinteractivity;
	class model2D {
	public:
		std::vector<mesh2D> meshes;
		std::string id;

		std::vector<transform2D*> instances;

		std::vector<std::pair<int, glm::vec3>> outlineShaderQueue;

		model2D(std::string id);

		void addToOutlineShaderQueue(int instanceIdx, glm::vec3 color);
		void renderOutlineShaderQueue(Shader outlineShader);

		void init();
		void renderInstances(Shader shader);
		void renderInstance(Shader shader, transform2D* transform, glm::vec3 color = glm::vec3(-1.0));
		void calcRectBorder2D();
		void generateInstance(glm::vec2 pos, glm::vec2 size = glm::vec2(1.0), glm::vec3 rotation = glm::vec3(0.0));
		void initInstances();

		rectBorder2D getInstanseBorder(unsigned int instanceIdx);
		unsigned int getInstaneIdxById(std::string id);

	private:
		BufferObject posVBO, sizeVBO;
		rectBorder2D border;

		std::string currentId;
		std::string generateId();
	};
}

#endif // !MODEL2D_H
