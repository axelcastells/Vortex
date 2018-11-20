#pragma once
#include "VRenderer.h"

namespace Vortex {
	class VEngine {
	public:
		VEngine(VEngine const&) = delete;
		VEngine& operator=(VEngine const&) = delete;

		static std::shared_ptr<VEngine> Instance() {
			static std::shared_ptr<VEngine> instance{ new VEngine };
			return instance;
		}

		VRenderer& GetRenderer() {
			return *renderer;
		}

	private:
		VEngine();

		VRenderer* renderer;
	};
}