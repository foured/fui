#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

namespace fui{
	class texture {
	public:
		unsigned int id;

		texture();
		texture(std::string path);
	};
}

#endif // !TEXTURE_H
