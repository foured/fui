#include "model2d.h"
#include "fuiscene.h"


fui::model2D::model2D(std::string id)
	: id(id), currentId("aaaaaaaa") { //selectedInstanceId("")
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
	for (int i = 0, s = outlineShaderQueue.size(); i < s; i++) {
		transform2D* instance = instances[outlineShaderQueue[i].first];
		modelOutline.renderInstance(outlineShader, instance->position, instance->size, outlineShaderQueue[i].second);
	}
	outlineShaderQueue.clear();
}

void fui::model2D::prepareOutlineShader(Shader shader) {
	outlineShader = shader;
	outlineShader.activate();
}

void fui::model2D::renderInstances(Shader shader) {
	shader.activate();
	sortInstancesByLayer();
	std::vector<glm::vec3> positions, sizes;
	for (unsigned int i = 0, size = instances.size(); i < size; i++) {
		bool hasOutline = false;
		for (int j = 0, s = outlineShaderQueue.size(); j < s; j++) {
			if (i == outlineShaderQueue[j].first) {
				hasOutline = true;
				break;
			}
		}
		if (!hasOutline) {
			positions.push_back(glm::vec3(instances[i]->position, 0.0));
			sizes.push_back(glm::vec3(instances[i]->size, 1.0));
		}
		else {
			oPositions.push_back(glm::vec3(instances[i]->position, 0.0));
			oSizes.push_back(glm::vec3(instances[i]->size, 1.0));
		}
	}

	if (positions.size() > 0) {
		posVBO.bind();
		posVBO.updateData<glm::vec3>(0, positions.size(), &positions[0]);

		sizeVBO.bind();
		sizeVBO.updateData<glm::vec3>(0, positions.size(), &sizes[0]);

		for (int i = 0, len = meshes.size(); i < len; i++) {
			meshes[i].render(positions.size(), shader);
		}
	}

}

void fui::model2D::renderOutlinedInstances(Shader shader, Shader outlineShader) {
	for (int i = 0, s = oSizes.size(); i < s; i++) {
		renderInstance(outlineShader, instances[outlineShaderQueue[i].first], outlineShaderQueue[i].second);
	}
	shader.activate();
	if (oPositions.size() > 0) {
		posVBO.bind();
		posVBO.updateData<glm::vec3>(0, oPositions.size(), &oPositions[0]);

		sizeVBO.bind();
		sizeVBO.updateData<glm::vec3>(0, oPositions.size(), &oSizes[0]);

		for (int i = 0, len = meshes.size(); i < len; i++) {
			meshes[i].render(oPositions.size(), shader);
		}
	}
	oPositions.clear();
	oSizes.clear();
	outlineShaderQueue.clear();
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
	transform2D* instance = new transform2D(pos, size, rotation, this, &border, generateId());
	instance->interactivity.setSIM(sim);
	instances.push_back(instance);
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

void fui::model2D::sortInstancesByLayer() {
	for (unsigned int i = 1; i < instances.size(); i++) {
		for (unsigned int j = 0; j < instances.size() - i; j++) {
			if (instances[j]->orderInLayer > instances[j + 1]->orderInLayer) {
				transform2D* temp = instances[j];
				instances[j] = instances[j + 1];
				instances[j + 1] = temp;
			}
		}
	}
}

//bool fui::model2D::canBeSelected(transform2D* instance) {
//	std::string ciid = instance->indstanceId;
//
//	if (ciid == selectedInstanceId || selectedInstanceId == "") {
//		return true;
//	}
//	else {
//		bool can = !instances[getInstaneIdxById(selectedInstanceId)]->border.isDotInRect(scene::getMousePosInNDC());
//		return can;
//	}
//}

void fui::model2D::cleanup() {
	for (mesh2D m : meshes) {
		m.cleanup();
	}
}

void fui::model2D::init(){}