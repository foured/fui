#ifndef FUISCENE_H
#define FUISCENE_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../io/keyboard.h"
#include "../io/mouse.h"

namespace fui {
	class scene {
	public:
		GLFWwindow* window;
		const char* title;
		static unsigned int width, height;
		glm::vec4 windowColor;

		scene(int width = 800, int height = 800, const char* title = "Hello OpenGL!", glm::vec4 color = glm::vec4(0.41, 0.62, 0.69, 1.0));

		void processInput();
		int init();
		void update();
		void newFrame();
		bool shouldClose();
		void terminate();
		void setShouldClose(bool value);

		static glm::vec2 getMousePosInNDC();
		static glm::vec2 getMousePosInPixels();

		static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

		static double getDX();
		static double getDY();
		static bool mouseButton(int button);
		static bool mouseButtonWentUp(int button);
		static bool mouseButtonWentDown(int button);
	private:
		void rememberMouseInputs();

		static double mouseDX, mouseDY;
		static bool mouseButtons[];
		static bool mouseButtonsWentUp[];
		static bool mouseButtonsWentDown[];
	};
}
#endif // !FUISCENE_H
