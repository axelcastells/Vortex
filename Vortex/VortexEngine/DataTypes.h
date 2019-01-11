#pragma once

namespace Vortex {
	
	class Vector2D {
		float x, y;
	};

	class Vector3D {
		float x, y, z;
	};
	
	namespace Graphics {
		typedef enum ShaderType { VERTEX, FRAGMENT, GEOMETRY };
		struct Buffer {
			unsigned int VAO, VBO;
		};

	}

	//namespace 
}