#pragma once
#include "Kaluopch.h"
#include "Core.h"
#include "Events/Event.h"
#include "KaluoEngine/Events/ApplicationEvent.h"
#include "Window.h"

namespace KaluoEngine{

	class KALUO_API Application
	{
	public:
		Application();
		virtual ~Application(); 

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		//only have one application for entire application as unique pointer and it will shut down when terminal ends 
		std::unique_ptr<Window> m_Window;
		//Window* m_Window;
		bool m_Running = true;
	};


	//To be defined in client
	Application* CreateApplication();
}