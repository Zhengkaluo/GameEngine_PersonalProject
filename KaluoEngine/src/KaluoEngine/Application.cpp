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

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
		
		//Steps: Vertex Array + Vertex Buffer + Index Buffer
		//Shader, use default shader

		// generate vertex array object names in here 'm_VertexArray', and bind the name with the object
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		
		// generate buffer object names and bind the vertex attributes target
		// we dont need to genearte here code by code (so thtere are three commend out lines) 
		// since we have a openglBuffer class for generation now
		// instead we use the unique pointer of vertex buffer and construct it
		// glGenBuffers(1, &m_VertexBuffer);
		// glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		// //upload data to gpu, static draw meaning we are not continuing refreshing
		// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexBuffer->Bind();

		
		//enable the first vertex attribute
		glEnableVertexAttribArray(0);

		//define an array of generic vertex attribute data, stride meaning each column of 3*3 has 3 float data (每行有三个float)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		// same as buffer, we have now a interface class of index buffer class to genearte and bind for us
		// so the following three codes are commended
		// glGenBuffers(1, &m_IndexBuffer);
		// // what order to draw, target: Vertex array indices
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
		
		//source code of shader
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			//varying variable 
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			//update in forward order
			for (Layer* EachLayer : m_LayerStack)
				EachLayer->OnUpdate();

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