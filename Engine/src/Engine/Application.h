#pragma once

#include "Core.h"
#include "Window.h"

#include "Engine/LayerStack.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

namespace Engine {

	class ENGINE_API Application {
	public:
		Application();

		virtual ~Application();		// virtual because this class will be subclassed by SandBox app
									// when this destructor is called, Sandbox destructor must be called too

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		LayerStack m_LayerStack;

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	private:
		static Application* s_Instance;
	};

	// To be defined in a CLIENT
	Application* CreateApplication();

}


