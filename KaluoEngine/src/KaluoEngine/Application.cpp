#include "Kaluopch.h"
#include "Application.h"

//#include <glad/glad.h>

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
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) 
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

		m_VertexArray.reset(VertexArray::Create());

		// generate vertex array object names in here 'm_VertexArray', and bind the name with the object
		// 2022-8-19 we are going to make it abstract move it to openglvertexarray.h
		/*	glGenVertexArrays(1, &m_VertexArray);
			glBindVertexArray(m_VertexArray);*/

		
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		
		//	generate buffer object names and bind the vertex attributes target
		//	we dont need to genearte here code by code (so thtere are three commend out lines) 
		//	since we have a openglBuffer class for generation now
		//	 instead we use the unique pointer of vertex buffer and construct it
		//	glGenBuffers(1, &m_VertexBuffer);
		//	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		//	//upload data to gpu, static draw meaning we are not continuing refreshing
		//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//	m_VertexBuffer->Bind();
		//	constructing buffer layout class by sending bufferelements
		//	2022-8-19: and part of vertex attribt dealing function is moved to openglvertexarray AddVertexBuffer
		BufferLayout Elementlayout{
			//takes in buffer elements initializer_list
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color "}
		};
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexBuffer->SetLayout(Elementlayout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		/* // 2022-8-19 we are going to make it abstract
		// this is moving to openglvertexarray class AddVertexBuffer()
		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			//enable the first vertex attribute
			glEnableVertexAttribArray(index);
			//define an array of generic vertex attribute data, stride meaning each column of 3*3 has 3 float data (每行有三个float)
			//2022-8-18: conversion of ShaderDataType into gl function parameters
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}*/

		
		// same as buffer, we have now a interface class of index buffer class to genearte and bind for us
		// so the following three codes are commended
		// glGenBuffers(1, &m_IndexBuffer);
		// // what order to draw, target: Vertex array indices
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		m_SquareVA.reset(VertexArray::Create());

		float SqaureVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f, 
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> SquareVB; 
		SquareVB.reset(VertexBuffer::Create(SqaureVertices, sizeof(SqaureVertices)));
		BufferLayout SquareVBlayout{
			//takes in buffer elements initializer_list
			{ ShaderDataType::Float3, "a_Position" },
		};
		SquareVB->SetLayout(SquareVBlayout);
		m_SquareVA->AddVertexBuffer(SquareVB);

		unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0};
		std::shared_ptr<IndexBuffer>SquareIndexBuffer; 
		SquareIndexBuffer.reset(IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
		m_SquareVA->SetIndexBuffer(SquareIndexBuffer);

		//source code of shader
		//2022-8-23 adding view projeciton matrix
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
	
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color  = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;

			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		//source code of shader
		std::string BlueShadervertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			
			uniform mat4 u_ViewProjection;			

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string BlueShaderfragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec4 v_Color;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		m_BlueShader.reset(new Shader(BlueShadervertexSrc, BlueShaderfragmentSrc));

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
			//2022-8-21 using renderercommand to deal with specific actions now
			//glClearColor(0.1f, 0.1f, 0.1f, 1);
			//glClear(GL_COLOR_BUFFER_BIT);
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
			m_Camera.SetRotation(45.0f);

			Renderer::BeginScene(m_Camera);
			//draw square in blue
			//2022-8-21 draw elements are moving to specific api to draw!
			//Renderer::Submit do the work!
			//m_BlueShader->Bind();
			//2022-8-23 uploade uniform matrix and moved UpLoadUniformMat4() to renderer to handle
			//m_BlueShader->UpLoadUniformMat4("u_ViewProjection", m_Camera.GetProjectionMatrix());
			Renderer::Submit(m_BlueShader, m_SquareVA);
			//m_Shader->Bind();
			//m_Shader->UpLoadUniformMat4("u_ViewProjection", m_Camera.GetProjectionMatrix());
			Renderer::Submit(m_Shader, m_VertexArray);

			Renderer::EndScene();

			//glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			//2022-8-19 this is moved to openglvertex array specific funtion to bind!
			//vertexarray->Bind() did the work!
			//glBindVertexArray(m_VertexArray);

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