#include "Kaluopch.h"
#include "Application.h"
#include "Kaluopch.h"
//#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Input.h"
using namespace std;


namespace KaluoEngine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		KALUO_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		//call constructor
		m_Window = std::unique_ptr<Window>(Window::Create());
		//set event call back function
		//event call back go in o windowData--EventCallbackFn
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));


		/*unsigned int id;
		glGenVertexArrays(1, &id);*/
		//m_Window = Window::Create();
		//print("constructing app");
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		//call the layer
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//check through event dispatcher
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//KALUO_CORE_TRACE("{0}", e);

		//update on backward order
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) 
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
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

			//update in forward order
			for (Layer* EachLayer : m_LayerStack)
				EachLayer->OnUpdate();

			//test if input instace is working
			//auto [x, y] = Input::GetMousePosition();
			//KALUO_CORE_TRACE("mouse pos: {0}, {1}", x, y);
			////#define GLFW_KEY_A   ---   65
			//auto IsAPressed = Input::IsKeyPressed(65);
			//KALUO_CORE_TRACE("Key 9 is Pressed {0}", IsAPressed);

			m_Window->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	

}