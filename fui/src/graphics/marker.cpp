#include "marker.h"

#define _USE_MATH_DEFINES
#include <math.h>

fui::marker::marker(glm::vec3 color) : color(color) {
	size = glm::vec3(0.02);
}

void fui::marker::init() {
	int noVertices = 16;
	float radius = 0.5;
	std::vector<float> vertices;
	for (double i = 0; i < 2 * M_PI; i += 2 * M_PI / noVertices) {
		vertices.push_back(cos(i) * radius);    //X coordinate
		vertices.push_back(sin(i) * radius);    //Y coordinate
		vertices.push_back(0.0);                //Z coordinate
		vertices.push_back(0.0);
		vertices.push_back(0.0);
	}
	std::vector<unsigned int> indices;
	for (int i = 1; i < noVertices; i++) {
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(0);
	}

	fui::mesh2D ret(color);
	ret.setup(fui::vertex::generateVertices(vertices), indices);
	meshes.push_back(ret);

	//render part
	std::vector<glm::vec3> positions, sizes;
	positions.emplace_back(0);
	positions.emplace_back(0);
	sizes.emplace_back(0);
	sizes.emplace_back(0);
	posVBO = BufferObject(GL_ARRAY_BUFFER);
	posVBO.generate();
	posVBO.bind();
	posVBO.setData<glm::vec3>(2, &positions[0], GL_DYNAMIC_DRAW);

	sizeVBO = BufferObject(GL_ARRAY_BUFFER);
	sizeVBO.generate();
	sizeVBO.bind();
	sizeVBO.setData<glm::vec3>(2, &sizes[0], GL_DYNAMIC_DRAW);

	for (unsigned int i = 0, size = meshes.size(); i < size; i++) {
		meshes[i].VAO.bind();

		posVBO.bind();
		posVBO.setAttPointer<glm::vec3>(3, 3, GL_FLOAT, 1, 0, 1);

		sizeVBO.bind();
		sizeVBO.setAttPointer<glm::vec3>(2, 3, GL_FLOAT, 1, 0, 1);

		ArrayObject::clear();
	}
}

void fui::marker::render(Shader shader, std::vector<glm::vec2> positions) {
	if (positions.size() > 0) {
		int noInstances = positions.size();
		shader.activate();

		std::vector<glm::vec3> rPositions, rSizes;
		rPositions.reserve(noInstances);
		rSizes.reserve(noInstances);
		for (glm::vec2 pos : positions) {
			rPositions.emplace_back(pos.x, pos.y, 0);
			rSizes.emplace_back(size);
		}

		posVBO.bind();
		posVBO.updateData<glm::vec3>(0, noInstances, &rPositions[0]);

		sizeVBO.bind();
		sizeVBO.updateData<glm::vec3>(0, noInstances, &rSizes[0]);

		for (int i = 0, len = meshes.size(); i < len; i++) {
			meshes[i].render(noInstances, shader);
		}
	}
}

void fui::marker::cleanup() {
	for (mesh2D mesh : meshes)
		mesh.cleanup();
}