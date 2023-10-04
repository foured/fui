#ifndef MODEL2D_H
#define MODEL2D_H

#include <string>

#include "mesh2d.h"
#include "shader.h"

#include "../algorithms/rectboreder2d.h"

namespace fui {
	class model2D {
	public:
		rectBorder2D border;
		std::vector<mesh2D> meshes;
		std::string id;

		model2D(std::string id);

		void init();
		void render(Shader shader);
		void calcRectBorder2D();
	};
}

#endif // !MODEL2D_H
