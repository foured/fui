#include "model2d.h"

fui::model2D::model2D(std::string id)
	: id(id) {}

void fui::model2D::renderInstances(Shader shader) {
	shader.activate();
	std::vector<glm::vec3> positions, sizes;
	for (unsigned int i = 0, size = instances.size(); i < size; i++) {
		positions.push_back(glm::vec3(instances[i]->position, 0.0));
		sizes.push_back(glm::vec3(instances[i]->size, 1.0));
	}

	posVBO.bind();
	posVBO.updateData<glm::vec3>(0, instances.size(), &positions[0]);

	sizeVBO.bind();
	sizeVBO.updateData<glm::vec3>(0, instances.size(), &sizes[0]);

	for (int i = 0, len = meshes.size(); i < len; i++) {
		meshes[i].render(instances.size());
	}
}

void fui::model2D::calcRectBorder2D() {
	for (int i = 0, len = meshes.size(); i < len; i++) {
		for (int j = 0, len1 = meshes[i].vertices.size(); j < len1; j += 3) {
			float val = meshes[i].vertices[j];
			if (border.min.x > val) border.min.x = val;
			if (border.max.x < val) border.max.x = val;

			val = meshes[i].vertices[j + 1];
			if (border.min.y > val) border.min.y = val;
			if (border.max.y < val) border.max.y = val;
		}
	}
}

void fui::model2D::generateInstance(glm::vec2 pos, glm::vec2 size, glm::vec3 rotation) {
	instances.push_back(new transform2D(pos, size, rotation, this, &border));
}

void fui::model2D::initInstances(){
	std::vector<glm::vec3> positions, sizes;

	for (unsigned int i = 0, size = instances.size(); i < size; i++) {
		positions.push_back(glm::vec3(instances[i]->position, 0.0));
		sizes.push_back(glm::vec3(instances[i]->size, 1.0));
	}

	posVBO = BufferObject(GL_ARRAY_BUFFER);
	posVBO.generate();
	posVBO.bind();
	posVBO.setData<glm::vec3>(instances.size(), &positions[0], GL_DYNAMIC_DRAW);

	sizeVBO = BufferObject(GL_ARRAY_BUFFER);
	sizeVBO.generate();
	sizeVBO.bind();
	sizeVBO.setData<glm::vec3>(instances.size(), &sizes[0], GL_DYNAMIC_DRAW);

	for (unsigned int i = 0, size = meshes.size(); i < size; i++) {
		meshes[i].VAO.bind();

		posVBO.bind();
		posVBO.setAttPointer<glm::vec3>(1, 3, GL_FLOAT, 1, 0, 1);

		sizeVBO.bind();
		sizeVBO.setAttPointer<glm::vec3>(2, 3, GL_FLOAT, 1, 0, 1);

		ArrayObject::clear();
	}
}

fui::rectBorder2D fui::model2D::getInstanseBorder(unsigned int instanceIdx) {
	transform2D* instance = instances[instanceIdx];
	return rectBorder2D(glm::vec2(border.min.x + instance->position.x, border.min.y + instance->position.y) * instance->size,
		glm::vec2(border.max.x + instance->position.x, border.max.y + instance->position.y) * instance->size);
}

void fui::model2D::init(){}