#pragma once
#include "Core.h"
namespace KaluoEngine{

	class KALUO_API Application
	{
	public:
		Application();
		virtual ~Application(); 

		void Run();
	};


	//To be defined in client
	Application* CreateApplication();
}