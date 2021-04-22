#pragma once

#ifdef EG_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv) {
	
	Engine::Log::Init();
	EG_CORE_WARN("Core Logger Init");
	EG_INFO("Client Logger Init");

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif 