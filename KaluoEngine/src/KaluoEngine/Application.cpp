#include "Kaluopch.h"
#include "Application.h"

//#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Log.h"
#include "Input.h"

#include "KaluoEngine/Renderer/RenderCommand.h"
#include "KaluoEngine/Renderer/Renderer.h"

#include "KaluoEngine/Renderer/OrthographicCamera.h"

using namespace std;


namespace KaluoEngine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	//2022-8-18 convert buffer layout datatype into opengl data type
	//2022-8-19 moved to openglvertexarray now!

	Application::Application()
	{
		KALUO_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		//call constructor
		m_Window = std::unique_ptr<Window>(Window::Create());
		//set event call back function
		//event call back go in o windowData--EventCallbackFn
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		//2022-8-26 timesteps/delta check where this 
		//sets glfwSwapInterval into 0 and it check if delta time works
		//m_Window->SetVSync(false);

		//2022-8-31 create our renderer
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);

		//2022-8-24 every renderer stuffs are being moved to sandbox app!
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
		while (m_Running) 
		{
			//2022-8-26 Delta time added
			float time = (float)glfwGetTime(); // Platform：:：GetTime
			TimeStep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			//2022-8-24 moving the whole rendering details into sandbox(client)

			//update in forward order
			for (Layer* EachLayer : m_LayerStack)
				EachLayer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* EachLayer : m_LayerStack)
				EachLayer->OnImGuiRender();
			m_ImGuiLayer->End();


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