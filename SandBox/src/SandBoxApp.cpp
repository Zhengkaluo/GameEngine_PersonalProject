
//#include "../KaluoEngine/KaluoEngine.h"
#include <KaluoEngine.h>
//#include <stdio.h>
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public KaluoEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f), m_CameraRotation(0.f), m_SqaurePosition(0.f)
	{
		//Steps: Vertex Array + Vertex Buffer + Index Buffer
		//Shader, use default shader
		m_VertexArray.reset(KaluoEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		KaluoEngine::BufferLayout Elementlayout{
			//takes in buffer elements initializer_list
			{ KaluoEngine::ShaderDataType::Float3, "a_Position" },
			{ KaluoEngine::ShaderDataType::Float4, "a_Color "}
		};
		std::shared_ptr<KaluoEngine::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(KaluoEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexBuffer->SetLayout(Elementlayout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<KaluoEngine::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(KaluoEngine::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		m_SquareVA.reset(KaluoEngine::VertexArray::Create());

		float SqaureVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		std::shared_ptr<KaluoEngine::VertexBuffer> SquareVB;
		SquareVB.reset(KaluoEngine::VertexBuffer::Create(SqaureVertices, sizeof(SqaureVertices)));
		KaluoEngine::BufferLayout SquareVBlayout{
			//takes in buffer elements initializer_list
			{ KaluoEngine::ShaderDataType::Float3, "a_Position" },
		};
		SquareVB->SetLayout(SquareVBlayout);
		m_SquareVA->AddVertexBuffer(SquareVB);

		unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<KaluoEngine::IndexBuffer>SquareIndexBuffer;
		SquareIndexBuffer.reset(KaluoEngine::IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
		m_SquareVA->SetIndexBuffer(SquareIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
	
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color  = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

		m_Shader.reset(new KaluoEngine::Shader(vertexSrc, fragmentSrc));

		//source code of shader
		std::string BlueShadervertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			
			uniform mat4 u_ViewProjection;			
			uniform mat4 u_Transform;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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
		m_BlueShader.reset(new KaluoEngine::Shader(BlueShadervertexSrc, BlueShaderfragmentSrc));
	}

	void OnUpdate(KaluoEngine::TimeStep timestep) override
	{
		//2022-8-26 getting timesteps which calculated in application run function
		KALUO_TRACE("DeltaTIme {0}, {1}ms", timestep.GetSeconds(), timestep.GetMillseconds());
		//operator casting time step into a float
		float DeltaTime = timestep;

		//2022-8-24 using polling system to move the camera
		if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * DeltaTime;
		else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * DeltaTime;

		if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * DeltaTime;
		else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * DeltaTime;
		
		if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_A))
			m_CameraRotation += m_CameraRotateSpeed * DeltaTime;
		else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_D))
			m_CameraRotation -= m_CameraRotateSpeed * DeltaTime;

		KaluoEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		KaluoEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		KaluoEngine::Renderer::BeginScene(m_Camera);

		//2022-8-28 create a transfom matrix based on vec3 squareposition 
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SqaurePosition);
		//10% scale matrix
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		//render 25 different small sqaure for testing tranform matrix
		for (int y = 0; y < 5; y++) 
		{
			for (int x = 0; x < 5; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				KaluoEngine::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
			}
		}
		
		//KaluoEngine::Renderer::Submit(m_Shader, m_VertexArray);

		KaluoEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		/*ImGui::Begin("Kaluo Engine Info:");
		ImGui::Text("Hello World");
		ImGui::End();*/

	}

	void OnEvent(KaluoEngine::Event& event) override
	{
		//KALUO_TRACE("{0} event update", event);
		//if (event.GetEventType() == KaluoEngine::EventType::KeyPressed)
		//{
		//	KaluoEngine::KeyPressedEvent& e = (KaluoEngine::KeyPressedEvent&)event;
		//	//KALUO_TRACE("key code {0}", (char)e.GetKeyCode());
		//	if (e.GetKeyCode() == KALUO_KEY_TAB)
		//	{
		//		KALUO_TRACE("Tab key is pressed (event)");
		//	}
		//}

		KaluoEngine::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KaluoEngine::KeyPressedEvent>(KALUO_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(KaluoEngine::KeyPressedEvent& event) 
	{
		//KALUO_INFO("{0} key is pressed!", event.GetKeyCode());
		
		return false;
	}

private:
	std::shared_ptr<KaluoEngine::Shader> m_Shader;
	std::shared_ptr<KaluoEngine::VertexArray> m_VertexArray;

	//sqaure vertex array
	std::shared_ptr<KaluoEngine::VertexArray> m_SquareVA;
	std::shared_ptr<KaluoEngine::Shader> m_BlueShader;

	KaluoEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;

	//in a second moved 1.3f unit and 180 degree
	float m_CameraMoveSpeed = 1.3f;
	float m_CameraRotateSpeed = 180.0f;
};

class Sandbox : public KaluoEngine::Application
{
public:
	Sandbox()
	{
		//std::("constructing sandbox...");
		PushLayer(new ExampleLayer());
		//PushOverlay(new KaluoEngine::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

//int main() 
//{
//	Sandbox* NewSandBox = new Sandbox();
//	NewSandBox->Run();
//	delete NewSandBox;
//}

//return new sandbox when application is needed to be created
KaluoEngine::Application* KaluoEngine::CreateApplication()
{
	return new Sandbox();
}