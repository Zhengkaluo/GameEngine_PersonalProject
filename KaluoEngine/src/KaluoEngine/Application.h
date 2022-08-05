#pragma once
#include "Kaluopch.h"
#include "Core.h"
#include "KaluoEngine/Events/Event.h"
#include "KaluoEngine/Events/ApplicationEvent.h"
#include "KaluoEngine/LayerStack.h"
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
		//Window* m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;

	private:
		//singleton application
		static Application* s_Instance;
	};


	//To be defined in client
	Application* CreateApplication();
}