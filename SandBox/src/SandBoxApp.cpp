
//#include "../KaluoEngine/KaluoEngine.h"
#include <KaluoEngine.h>
//#include <stdio.h>
#include "imgui/imgui.h"
class ExampleLayer : public KaluoEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example Layer")
	{
		//testing glm if its working
		//auto cam = camera(5.0f, { 0.5f, 0.5f });
	}

	void OnUpdate() override
	{
		//KALUO_INFO("Example Layer Update");

		if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_TAB)) 
		{
			KALUO_TRACE("tab key is pressed! (poll)");
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(KaluoEngine::Event& event) override
	{
		//KALUO_TRACE("{0} event update", event);
		if (event.GetEventType() == KaluoEngine::EventType::KeyPressed)
		{
			KaluoEngine::KeyPressedEvent& e = (KaluoEngine::KeyPressedEvent&)event;
			//KALUO_TRACE("key code {0}", (char)e.GetKeyCode());
			if (e.GetKeyCode() == KALUO_KEY_TAB)
			{
				KALUO_TRACE("Tab key is pressed (event)");
			}

		}
	}
};

class Sandbox : public KaluoEngine::Application
{
public:
	Sandbox()
	{
		//std::("constructing sandbox...");
		PushLayer(new ExampleLayer());
		//PushOverlay(new KaluoEngine::ImGuiLayer());
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