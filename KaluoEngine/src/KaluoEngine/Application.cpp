#include "Kaluopch.h"
#include "Application.h"
#include "Kaluopch.h"
#include <GLFW/glfw3.h>
#include "Events/ApplicationEvent.h"
#include "Log.h"

using namespace std;

namespace KaluoEngine {
	Application::Application()
	{
		//call constructor
		m_Window = std::unique_ptr<Window>(Window::Create());
		//m_Window = Window::Create();
		//print("constructing app");
	}
	Application::~Application()
	{

	}

	void Application::Run()
	{
		//WindowResizeEvent e(1280, 720);
		////KALUO_TRACE(e);

		//if (e.IsInCategory(EventCategoryApplication))
		//{
		//	KALUO_TRACE(e);
		//}
		//if (e.IsInCategory(EventCategoryInput))
		//{
		//	KALUO_TRACE(e);
		//}

		////printf("Application run");
		//while (true);

		while (m_Running) 
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}