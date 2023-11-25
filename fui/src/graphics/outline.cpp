#include "outline.h"

void fui::outline::initOutline(std::vector<mesh2D> nMeshes)  {
	meshes = nMeshes;

	std::vector<glm::vec3> positions(1, glm::vec3(0.0)), sizes(1, glm::vec3(1.0));

	posVBO = BufferObject(GL_ARRAY_BUFFER);
	posVBO.generate();
	posVBO.bind();
	posVBO.setData<glm::vec3>(1, &positions[0], GL_DYNAMIC_DRAW);

	sizeVBO = BufferObject(GL_ARRAY_BUFFER);
	sizeVBO.generate();
	sizeVBO.bind();
	sizeVBO.setData<glm::vec3>(1, &sizes[0], GL_DYNAMIC_DRAW);

	for (unsigned int i = 0, size = meshes.size(); i < size; i++) {
		meshes[i].VAO.bind();

		posVBO.bind();
		posVBO.setAttPointer<glm::vec3>(3, 3, GL_FLOAT, 1, 0, 1);

		sizeVBO.bind();
		sizeVBO.setAttPointer<glm::vec3>(2, 3, GL_FLOAT, 1, 0, 1);

		ArrayObject::clear();
	}
}
void fui::outline::renderInstance(Shader shader, glm::vec2 position, glm::vec2 size, glm::vec3 color) {
	shader.activate();
	shader.set3Float("oColor", color);
	std::vector<glm::vec3> positions, sizes;

	positions.push_back(glm::vec3(position, 0.0));
	sizes.push_back(glm::vec3(size, 1.0));

	posVBO.bind();
	posVBO.updateData<glm::vec3>(0, sizes.size(), &positions[0]);

	sizeVBO.bind();
	sizeVBO.updateData<glm::vec3>(0, sizes.size(), &sizes[0]);

	for (int i = 0, len = meshes.size(); i < len; i++) {
		meshes[i].render(sizes.size(), shader);
	}
}