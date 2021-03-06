#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Engine {

	class ENGINE_API Application {
	public:
		Application();

		virtual ~Application();		// virtual because this class will be subclassed by SandBox app
									// when this destructor is called, Sandbox destructor must be called too	???

		void Run();

	};

	// To be defined in a CLIENT
	Application* CreateApplication();

}


