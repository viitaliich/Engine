#include "pch.h"

#include "Application.h"

#include <GLFW/glfw3.h>

// this ???
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1) 

namespace Engine {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
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

	void Application::OnEvent(Event& e)
	{
		//???
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		EG_CORE_TRACE("{0}", e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
