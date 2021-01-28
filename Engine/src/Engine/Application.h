#pragma once

#include "Core.h"

namespace Engine {

	class ENGINE_API Application {
	public:
		Application();

		virtual ~Application();		// virtual because this class will be subclassed by SandBox app
									// when this destructor is called, Sandbox destructor must be callsed too	???

		void Run();

	};

	// To be defined in a CLIENT
	Application* CreateApplication();

}


