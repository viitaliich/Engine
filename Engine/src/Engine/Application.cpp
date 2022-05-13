#include "pch.h"

#include "Application.h"

#include "Engine/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Engine {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {
		
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);		// set color buffer will be cleared with
			glClear(GL_COLOR_BUFFER_BIT);	// clears setted buffer
			m_Window->OnUpdate();
		}

	}

}
