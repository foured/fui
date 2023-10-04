#include "mesh2d.h"

std::vector<fui::vertex> generateVertices(std::vector<float> verticesData) {
	int vsize = verticesData.size() / 5;
	std::vector<fui::vertex> vertices(vsize);

	for (int i = 0; i < vsize; i++) {
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

void fui::mesh2D::setup(std::vector<float> _vertices, std::vector<unsigned int> _indices) {
	this->indices = _indices;
	this->vertices = _vertices;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void fui::mesh2D::render(GLuint renderType) {
	glBindVertexArray(VAO);
	glPolygonMode(GL_FRONT_AND_BACK, renderType);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}