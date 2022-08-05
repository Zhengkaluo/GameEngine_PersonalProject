
//#include "../KaluoEngine/KaluoEngine.h"
#include <KaluoEngine.h>
#include <stdio.h>

class ExampleLayer : public KaluoEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example Layer")
	{

	}

	void OnUpdate() override
	{
		KALUO_INFO("Example Layer Update");
	}

	void OnEvent(KaluoEngine::Event& event) override
	{
		KALUO_TRACE("{0} event update", event);
	}
};

class Sandbox : public KaluoEngine::Application
{
public:
	Sandbox()
	{
		//std::("constructing sandbox...");
		PushLayer(new ExampleLayer());
		PushOverlay(new KaluoEngine::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

//int main() 
//{
//	Sandbox* NewSandBox = new Sandbox();
//	NewSandBox->Run();
//	delete NewSandBox;
//}

//return new sandbox when application is needed to be created
KaluoEngine::Application* KaluoEngine::CreateApplication()
{
	return new Sandbox();
}