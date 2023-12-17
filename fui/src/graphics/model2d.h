#ifndef MODEL2D_H
#define MODEL2D_H

#include <string>
#include <vector>

#include "mesh2d.h"
#include "shader.h"
#include "outline.h"

#include "../algorithms/rectboreder2d.h"
#include "../algorithms/transform2d.h"
#include "../algorithms/selectedItemManager.h"

namespace fui {
	class transform2D;
	class uiinteractivity;
	class selectedItemManager;

	class model2D {
	public:
		std::vector<mesh2D> meshes;
		std::string id;
		outline modelOutline;

		std::vector<transform2D*> instances;
		selectedItemManager* sim;
		std::vector<std::pair<int, glm::vec3>> outlineShaderQueue;

		model2D(std::string id);

		void addToOutlineShaderQueue(int instanceIdx, glm::vec3 color);
		void renderOutlineShaderQueue(Shader outlineShader);
		void prepareOutlineShader(Shader shader);

		void init();
		void renderInstances(Shader shader);
		void renderOutlinedInstances(Shader shader, Shader outlineShader);
		void renderInstance(Shader shader, transform2D* transform, glm::vec3 color = glm::vec3(-1.0));
		void calcRectBorder2D();
		void generateInstance(glm::vec2 pos, glm::vec2 size = glm::vec2(1.0), glm::vec3 rotation = glm::vec3(0.0));
		void initInstances();
		void sortInstancesByLayer();
		void cleanup();

		rectBorder2D getInstanseBorder(unsigned int instanceIdx);
		unsigned int getInstaneIdxById(std::string id);

		//bool canBeSelected(transform2D* instance);

	private:
		BufferObject posVBO, sizeVBO;
		rectBorder2D border;

		std::string currentId;
		std::string generateId();

		Shader outlineShader;
		std::vector<glm::vec3> oPositions, oSizes;
	};
}

#endif // !MODEL2D_H
