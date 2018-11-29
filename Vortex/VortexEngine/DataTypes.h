#pragma once

namespace Vortex {
	namespace Graphics {
		typedef enum ShaderType { VERTEX, FRAGMENT, GEOMETRY };
		struct Buffer {
			unsigned int VAO, VBO;
		};
		struct Vector2D {
			float x, y;
		};

		struct Vector3D {
			float x, y, z;
		};
	}

	//namespace 
}