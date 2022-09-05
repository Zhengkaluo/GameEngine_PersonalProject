
//#include "../KaluoEngine/KaluoEngine.h"
#include <KaluoEngine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public KaluoEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example Layer"), m_CameraController(1280.0f / 720.f)
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
		KaluoEngine::Ref<KaluoEngine::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(KaluoEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexBuffer->SetLayout(Elementlayout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		KaluoEngine::Ref<KaluoEngine::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(KaluoEngine::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_SquareVA.reset(KaluoEngine::VertexArray::Create());

		//2022-8-30 add texture coordinate
		//button left->button right->up right->up left
		float SqaureVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		KaluoEngine::Ref<KaluoEngine::VertexBuffer> SquareVB;
		SquareVB.reset(KaluoEngine::VertexBuffer::Create(SqaureVertices, sizeof(SqaureVertices)));
		KaluoEngine::BufferLayout SquareVBlayout{
			//takes in buffer elements initializer_list
			{ KaluoEngine::ShaderDataType::Float3, "a_Position" },
			{ KaluoEngine::ShaderDataType::Float2, "a_TextureCoord"},
		};
		SquareVB->SetLayout(SquareVBlayout);
		m_SquareVA->AddVertexBuffer(SquareVB);

		unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		KaluoEngine::Ref<KaluoEngine::IndexBuffer>SquareIndexBuffer;
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
		//2022-8-29 change to abstract class creation
		m_Shader = (KaluoEngine::Shader::Create("VertexPos Color shader", vertexSrc, fragmentSrc));

		//Shader::Create("assets/shader/Texture.glsl");

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

		std::string FlatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec4 v_Color;

			uniform vec3 u_Color;

			void main()
			{
				color =vec4(u_Color, 1.0f);
			}
		)";
		//2022-8-29 Triangle change to abstract class creation
		m_FlatColorShader = KaluoEngine::Shader::Create("Flat color shader", BlueShadervertexSrc, FlatColorShaderFragmentSrc);
		
		//2022-8-30 TextureShader
		//2022-9-1 moving the texture.glsl to handle shader create
		//2022-9-2 using shaderlirary to store and handle all shader create and load
		auto m_TextureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		
		m_Texture = KaluoEngine::Texture2D::Create("assets/textures/Checkerboard.png");
		//2022-8-31 testing alpha channel rendering
		m_LogoTexture = KaluoEngine::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<KaluoEngine::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<KaluoEngine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
}

	void OnUpdate(KaluoEngine::TimeStep timestep) override
	{
		//operator casting time step into a float
		//KALUO_TRACE("DeltaTIme {0}, {1}ms", timestep.GetSeconds(), timestep.GetMillseconds());
		
		//2022-8-24 using polling system to move the camera
		//2022-9-5 all camera stuffs move into camera controller
		m_CameraController.OnUpdate(timestep);

		//render stuffs
		KaluoEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		KaluoEngine::RenderCommand::Clear();

		//2022-9-5 move all camera handling into camera controller class
		/*m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);*/

		KaluoEngine::Renderer::BeginScene(m_CameraController.GetCamera());
		//2022-9-4 2Drenderer class planning
		//KaluoEngine::Renderer2D::BeginScene2D(m_Camera);
		//KaluoEngine::Renderer2D::DrawCircle(...);


		//2022-8-28 create a transfom matrix based on vec3 squareposition 
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SqaurePosition);
		//10% scale matrix
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		//some goals of material system
		/*
		KaluoEngine::MaterialRef material = new KaluoEngine::Material(m_FlatColorShader);
		KaluoEngine::MaterialInstanceRef materialinstance = new KaluoEngine::MaterialInstance(material);

		materialinstance->Set("uColor", RedColor);
		materialinstance->Set("u+AlbedoMap", texture);
		*/

		//2022-8-29 temporary cast the shader into openglshader and bind it
		std::dynamic_pointer_cast<KaluoEngine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<KaluoEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		//render 25 different small sqaure for testing tranform matrix
		for (int y = 0; y < 20; y++) 
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				KaluoEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		//2022-9-2 Using ShaderLIbrary to handle shader loading (meaning no more loacl varaibles)
		auto m_TextureShader = m_ShaderLibrary.Get("Texture");

		//2022-8-30 big sqaure with texture
		m_Texture->Bind();
		KaluoEngine::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//2022-8-31 adding alpha channel into the rendering 
		m_LogoTexture->Bind();
		KaluoEngine::Renderer::Submit(m_TextureShader, m_SquareVA, 
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		//KaluoEngine::Renderer::Submit(m_Shader, m_VertexArray);

		KaluoEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Kaluo Engine Info:");
		ImGui::Text("Hello World");

		//2022-8-29 
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();

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
		
		m_CameraController.OnEvent(event);
	}

	bool OnKeyPressedEvent(KaluoEngine::KeyPressedEvent& event) 
	{
		//KALUO_INFO("{0} key is pressed!", event.GetKeyCode());
		
		return false;
	}

private:
	//2022-9-2 holding shader library
	KaluoEngine::ShaderLibrary m_ShaderLibrary;

	//2022-8-30 using own smart pointers now.
	KaluoEngine::Ref<KaluoEngine::Shader> m_Shader;
	KaluoEngine::Ref<KaluoEngine::VertexArray> m_VertexArray;

	//sqaure vertex array
	KaluoEngine::Ref<KaluoEngine::VertexArray> m_SquareVA;
	KaluoEngine::Ref<KaluoEngine::Shader> m_FlatColorShader;

	//2022-8-30 texture2D 
	KaluoEngine::Ref<KaluoEngine::Texture2D> m_Texture, m_LogoTexture;

	KaluoEngine::OrthographicCameraController m_CameraController;

	glm::vec3 m_CameraPosition;
	float m_CameraRotation;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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