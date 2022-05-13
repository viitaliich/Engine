#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Engine {

	class ENGINE_API Application {
	public:
		Application();

		virtual ~Application();		// virtual because this class will be subclassed by SandBox app
									// when this destructor is called, Sandbox destructor must be called too	???

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in a CLIENT
	Application* CreateApplication();

}


