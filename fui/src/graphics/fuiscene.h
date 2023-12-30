#ifndef FUISCENE_H
#define FUISCENE_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../io/keyboard.h"
#include "../io/mouse.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include "../graphics/text.h"

#include "model2d.h"
#include "marker.h"
#include "parent.h"

namespace fui {
	class scene {
	public:
		static unsigned int width, height;
		FT_Library ft;
		TextRenderer textRenderer;
		std::vector<model2D*> models;

		scene(int width = 800, int height = 800, const char* title = "Hello OpenGL!", glm::vec4 color = glm::vec4(0.41, 0.62, 0.69, 1.0));

		void processInput();
		int init();
		void registerModel(model2D* model);
		void renderScene(Shader shader, Shader outlineShader, Shader textShader);
		void update();
		void newFrame();
		bool shouldClose();
		void terminate();
		void setShouldClose(bool value);
		void cleanup();

		static glm::vec2 getMousePosInNDC();
		static glm::vec2 getMousePosInPixels();

		static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

		static double getDX();
		static double getDY();
		static bool mouseButton(int button);
		static bool mouseButtonWentUp(int button);
		static bool mouseButtonWentDown(int button);

		model2D* getModelById(std::string modelId);

	private:
		GLFWwindow* window;
		const char* title;
		glm::vec4 windowColor;

		void rememberMouseInputs();

		static double mouseDX, mouseDY;
		static bool mouseButtons[];
		static bool mouseButtonsWentUp[];
		static bool mouseButtonsWentDown[];

		parent* iAmParent;
		static rectBorder2D border;
		marker marker;
	};
}
#endif // !FUISCENE_H
