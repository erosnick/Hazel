/*
* This is an independent project of an individual developer. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include "HazelPCH.h"
#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
public:

	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
	}

	void OnEvent(Hazel::Event& event) override
	{
		HAZEL_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Hazel::ImGuiLayer());
	}

	~Sandbox()
	{

	}

private:

};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}