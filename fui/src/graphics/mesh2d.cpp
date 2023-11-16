#include "mesh2d.h"

#include <iostream>

fui::mesh2D::mesh2D(glm::vec3 color)
	: color(color), hasTexture(false) {}

fui::mesh2D::mesh2D(texture texture) 
	: meshTexture(texture), hasTexture(true) {}

std::vector<fui::vertex> fui::vertex::generateVertices(std::vector<float> verticesData) {
	int vsize = verticesData.size();
	std::vector<fui::vertex> vertices(vsize);

	for (int i = 0; i < vsize; i += 5) {
		vertices[i].pos = {
			verticesData[i + 0],
			verticesData[i + 1],
			verticesData[i + 2]
		};
		vertices[i].texCoord = {
			verticesData[i + 3],
			verticesData[i + 4]
		};
	}

	return vertices;
}

void fui::mesh2D::setup(std::vector<vertex> _vertices, std::vector<unsigned int> _indices) {
	this->indices = _indices;
	this->vertices = _vertices;

	VAO.generate();
	VAO.bind();

	// generate/set EBO
	VAO["EBO"] = BufferObject(GL_ELEMENT_ARRAY_BUFFER);
	VAO["EBO"].generate();
	VAO["EBO"].bind();
	VAO["EBO"].setData<GLuint>(indices.size(), &this->indices[0], GL_STATIC_DRAW);

	// load data into vertex buffers
	VAO["VBO"] = BufferObject(GL_ARRAY_BUFFER);
	VAO["VBO"].generate();
	VAO["VBO"].bind();
	VAO["VBO"].setData<vertex>(vertices.size(), &this->vertices[0], GL_STATIC_DRAW);

	VAO["VBO"].bind();
	VAO["VBO"].setAttPointer<GLfloat>(0, 3, GL_FLOAT, 5, 0);
	VAO["VBO"].setAttPointer<GLfloat>(1, 2, GL_FLOAT, 5, 3);
	VAO["VBO"].clear();

	ArrayObject::clear();
}

void fui::mesh2D::render(unsigned int noInstances, Shader shader, GLuint renderType) {
	if (hasTexture) {
		glActiveTexture(GL_TEXTURE0);
		shader.setInt("hasTexture", 1);
	}
	else {
		shader.setInt("hasTexture", 0);
		shader.set3Float("color", color);
	}

	VAO.bind();
	VAO.draw(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, noInstances);
	ArrayObject::clear();

	glActiveTexture(GL_TEXTURE0);
}