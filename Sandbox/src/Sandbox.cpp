/*
* This is an independent project of an individual developer. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
*/
#include <iostream>
#include <Hazel.h>

class Sandbox : public Hazel::Application
{
public:
	Sandbox();
	~Sandbox();

private:

};

Sandbox::Sandbox()
{
}

Sandbox::~Sandbox()
{
}

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}