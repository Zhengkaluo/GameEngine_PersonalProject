#pragma once
#include "Kaluopch.h"
#include "Core.h"
#include "KaluoEngine/Events/Event.h"
#include "KaluoEngine/Events/ApplicationEvent.h"
#include "KaluoEngine/LayerStack.h"
#include "KaluoEngine/ImGui/ImGuiLayer.h"
#include "KaluoEngine/Renderer/VertexArray.h"
#include "KaluoEngine/Renderer/Shader.h"
#include "KaluoEngine/Renderer/Buffer.h"
#include "Window.h"

namespace KaluoEngine{

	class KALUO_API Application
	{
	public:
		Application();
		virtual ~Application(); 

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get(){ return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		//only have one application for entire application as unique pointer and it will shut down when terminal ends 
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		//Window* m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;

		//for context rendering
		//unsigned int m_VertexArray;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		//sqaure vertex array
		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_BlueShader;


	private:
		//singleton application
		static Application* s_Instance;
	};


	//To be defined in client
	Application* CreateApplication();
}