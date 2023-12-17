#include "texture.h"

fui::texture::texture() {}

fui::texture::texture(std::string path) {
	float startTime = glfwGetTime();
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nChannels, 0);
	unsigned int len = std::strlen(reinterpret_cast<const char*>(data));

	if (data) {
		GLint colorType = GL_RGB;
		if (nChannels == 1)
			colorType = GL_RED;
		else if (nChannels == 4)
			colorType = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, colorType, width, height, 0, colorType, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	std::cout << "Texture '" << path << "' size of " << len / 1024 << " KB was loaded in " << glfwGetTime() - startTime << " sec." << std::endl;
}

void fui::texture::bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}

void fui::texture::cleanup() {
	glDeleteTextures(1, &id);
}