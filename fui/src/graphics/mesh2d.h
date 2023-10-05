#ifndef MESH2D_H
#define MESH2D_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "vertexmemory.hpp"

namespace fui {
	struct vertex {
		glm::vec3 pos;
		glm::vec2 texCoord;

		static std::vector<struct vertex> generateVertices(std::vector<float> verticesData);
	};

	class mesh2D {
	public:
		//unsigned int VBO, VAO, EBO;
		ArrayObject VAO;

		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		void setup(std::vector<float> _vertices, std::vector<unsigned int> _indices);
		void render(unsigned int noInstances, GLuint renderType = GL_FILL);
	};
	
}
#endif // !MESH2D_H
