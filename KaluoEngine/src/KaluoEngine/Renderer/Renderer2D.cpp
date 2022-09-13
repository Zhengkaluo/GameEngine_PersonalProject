#include "Kaluopch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

#include "VertexArray.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>

//2022-9-10 using renderer2d api to do the job, no more dynamic casting
//#include "Platform/OpenGL/OpenGLShader.h"

namespace KaluoEngine {

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture> WhiteTexture;
	};

	//for controlling the memory when shutdown
	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();

		//using 2d storage to store the vertex array
		s_Data->QuadVertexArray = (VertexArray::Create());

		//2022-9-9 these datas are all for testing this api
		float SqaureVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> SquareVB;
		SquareVB.reset(VertexBuffer::Create(SqaureVertices, sizeof(SqaureVertices)));
		BufferLayout SquareVBlayout{
			//takes in buffer elements initializer_list
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TextureCoord"}
		};
		SquareVB->SetLayout(SquareVBlayout);
		s_Data->QuadVertexArray->AddVertexBuffer(SquareVB);

		unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer>SquareIndexBuffer;
		SquareIndexBuffer.reset(IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
		s_Data->QuadVertexArray->SetIndexBuffer(SquareIndexBuffer);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		//hard code the data
		uint32_t whitetextData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whitetextData, sizeof(uint32_t));

		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::ShutDown()
	{
		//destroy vertex array and all 2d data storage
		//it calls all delete function inside the s_Data properties
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		//2022-9-10 using renderer2d api to do the job, no more dynamic casting
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		//2022-9-10 using renderer2d api to do the job, no more dynamic casting
		(s_Data->TextureShader)->SetFloat4("u_Color", color);
		//2022-9-13 bind white texture here
		s_Data->WhiteTexture->Bind();
		//2022-9-10 handling transform matrix as position and scale
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();

		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		(s_Data->TextureShader)->SetFloat4("u_Color", glm::vec4(1.0f));
		(s_Data->TextureShader)->Bind();
		
		//instead of setting color, we set texture
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();

		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);

		//texture->UnBind();
	}


}