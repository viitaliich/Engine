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
		EG_INFO("ExampleLayer::Update");
	}

	void OnEvent(Engine::Event& event) override
	{
		EG_TRACE("Layer Event - {0}", event);
	}

};

class Sandbox : public Engine::Application{		// all specifiers stays unchanged, so why do we use public?

public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
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