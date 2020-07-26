#pragma once

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char* argv[])
{
	Hazel::Log::Init();

	HAZEL_CORE_WARN("Initialized Log!");
	HAZEL_INFO("Hello");

	auto app = Hazel::CreateApplication();

	app->Run();

	delete app;

	return 0;
}