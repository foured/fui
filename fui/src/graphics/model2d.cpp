#include "model2d.h"

fui::model2D::model2D(std::string id)
	: id(id), currentId("aaaaaaaa") {
}

std::string fui::model2D::generateId() {
	for (int i = currentId.length() - 1; i >= 0; i--) {
		if ((int)currentId[i] != (int)'z') {
			// increment then break
			currentId[i] = (char)(((int)currentId[i]) + 1);
			break;
		}
		else {
			currentId[i] = 'a';
		}
	}
	return currentId;
}

void fui::model2D::addToOutlineShaderQueue(int instanceIdx, glm::vec3 color) {
	std::pair<int, glm::vec3>a;
	a.first = instanceIdx;
	a.second = color;
	outlineShaderQueue.push_back(a);
}

void fui::model2D::renderOutlineShaderQueue(Shader outlineShader) {
	outlineShader.activate();
	std::vector<glm::vec3> positions = { glm::vec3(0) }, sizes = { glm::vec3(0) };
	for (int i = 0, s = outlineShaderQueue.size(); i < s; i++) {
		renderInstance(outlineShader, instances[outlineShaderQueue[i].first], outlineShaderQueue[i].second);
		/*positions.push_back(glm::vec3(instances[outlineShaderQueue[i].first]->position, 0.0));
		sizes.push_back(glm::vec3(instances[outlineShaderQueue[i].first]->size, 1.0));
		std::cout << sizes[i].x << " " << sizes[i].y << std::endl;*/
	}
	//posVBO.bind();
	//posVBO.updateData<glm::vec3>(0, sizes.size(), &positions[0]);

	//sizeVBO.bind();
	//sizeVBO.updateData<glm::vec3>(0, sizes.size(), &sizes[0]);

	//for (int i = 0, len = meshes.size(); i < len; i++) {
	//	meshes[i].render(sizes.size(), outlineShader);
	//}
	outlineShaderQueue.clear();
}

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
		meshes[i].render(instances.size(), shader);
	}
}

void fui::model2D::renderInstance(Shader shader, transform2D* transform, glm::vec3 color) {
	shader.activate();

	if (color != glm::vec3(-1.0)) {
		shader.set3Float("oColor", color);
	}

	std::vector<glm::vec3> positions, sizes;

	positions.push_back(glm::vec3(transform->position, 0.0));
	sizes.push_back(glm::vec3(transform->size, 1.0));

	posVBO.bind();
	posVBO.updateData<glm::vec3>(0, instances.size(), &positions[0]);

	sizeVBO.bind();
	sizeVBO.updateData<glm::vec3>(0, instances.size(), &sizes[0]);

	for (int i = 0, len = meshes.size(); i < len; i++) {
		meshes[i].render(instances.size(), shader);
	}
}
void fui::model2D::calcRectBorder2D() {
	for (int i = 0, len = meshes.size(); i < len; i++) {
		for (int j = 0, len1 = meshes[i].vertices.size(); j < len1; j++) {
			float val = meshes[i].vertices[j].pos.x;
			if (border.min.x > val) border.min.x = val;
			if (border.max.x < val) border.max.x = val;

			val = meshes[i].vertices[j].pos.y;
			if (border.min.y > val) border.min.y = val;
			if (border.max.y < val) border.max.y = val;
		}
	}
}

void fui::model2D::generateInstance(glm::vec2 pos, glm::vec2 size, glm::vec3 rotation) {
	instances.push_back(new transform2D(pos, size, rotation, this, &border, generateId()));
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
		posVBO.setAttPointer<glm::vec3>(3, 3, GL_FLOAT, 1, 0, 1);

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

unsigned int fui::model2D::getInstaneIdxById(std::string id) {
	for (int i = 0, s = instances.size(); i < s; i++) {
		if (instances[i]->indstanceId == id) return i;
	}
	return -1;
}

void fui::model2D::init(){}