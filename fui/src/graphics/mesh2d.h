#ifndef MESH2D_H
#define MESH2D_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "shader.h"
#include "vertexmemory.hpp"
#include "texture.h"

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

		std::vector<vertex> vertices;
		std::vector<unsigned int> indices;

		texture meshTexture;
		glm::vec3 color;
		bool hasTexture;

		mesh2D(glm::vec3 color = glm::vec3(1.0, 0.5, 0.2));
		mesh2D(texture texture);

		void setup(std::vector<vertex> _vertices, std::vector<unsigned int> _indices);
		void render(unsigned int noInstances, Shader shader, GLuint renderType = GL_FILL);
		void cleanup();
	};
	
}
#endif // !MESH2D_H
