#include "Application.h"
#include <stdio.h>
#include "Events/ApplicationEvent.h"
#include "Log.h"

using namespace std;

namespace KaluoEngine {
	Application::Application()
	{
		//print("constructing app");
	}
	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		//KALUO_TRACE(e);

		if (e.IsInCategory(EventCategoryApplication))
		{
			KALUO_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			KALUO_TRACE(e);
		}

		//printf("Application run");
		while (true);
	}
}