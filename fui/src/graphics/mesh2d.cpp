#include "mesh2d.h"

std::vector<fui::vertex> fui::vertex::generateVertices(std::vector<float> verticesData) {
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

	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices[0], GL_STATIC_DRAW);


	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	VAO.generate();
	VAO.bind();

	// generate/set EBO
	VAO["EBO"] = BufferObject(GL_ELEMENT_ARRAY_BUFFER);
	VAO["EBO"].generate();
	VAO["EBO"].bind();
	VAO["EBO"].setData<GLuint>(this->indices.size(), &this->indices[0], GL_STATIC_DRAW);

	// load data into vertex buffers
	VAO["VBO"] = BufferObject(GL_ARRAY_BUFFER);
	VAO["VBO"].generate();
	VAO["VBO"].bind();
	VAO["VBO"].setData<GLfloat>(vertices.size(), &this->vertices[0], GL_STATIC_DRAW);

	VAO["VBO"].bind();
	VAO["VBO"].setAttPointer<GLfloat>(0, 3, GL_FLOAT, 0, 0);
	VAO["VBO"].clear();

	ArrayObject::clear();
}

void fui::mesh2D::render(unsigned int noInstances, GLuint renderType) {
	//glBindVertexArray(VAO);
	//glPolygonMode(GL_FRONT_AND_BACK, renderType);
	//glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0, noInstances);
	//glBindVertexArray(0);

	VAO.bind();
	VAO.draw(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, noInstances);
	ArrayObject::clear();
}