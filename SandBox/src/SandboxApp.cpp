#include "pch.h"
#include <Engine.h>		// For this dirrectory (Solution)\Engine\src is included to additional dirrectories on properties

class Sandbox : public Engine::Application{		// all specifiers stays unchanched, so why do we use public?

public:
	Sandbox() {

	}

	~Sandbox() {

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