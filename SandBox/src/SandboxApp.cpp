#include "pch.h"
#include <Engine.h>		// For this directory (Solution)\Engine\src is included to additional directories on properties

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Engine::Input::IsKeyPressed(EG_KEY_TAB))
			EG_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Engine::Event& event) override
	{
		if (event.GetEventType() == Engine::EventType::KeyPressed)
		{
			Engine::KeyPressedEvent& e = (Engine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == EG_KEY_TAB)
				EG_TRACE("Tab key is pressed (event)!");
			EG_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Engine::Application{		// all specifiers stays unchanged, so why do we use public?

public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Engine::ImGuiLayer());
	}

	~Sandbox() 
	{

	}

};

Engine::Application* Engine::CreateApplication() {
	return new Sandbox();
}

//int main() {
//	Sandbox* sandbox = new Sandbox();
//	sandbox->Run();
//	delete sandbox;
//}