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
		Ref<Shader> FlatColorShader;
	};

	//for controlling the memory when shutdown
	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();

		//using 2d storage to store the vertex array
		s_Data->QuadVertexArray = (VertexArray::Create());

		//2022-9-9 these datas are all for testing this api
		float SqaureVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		Ref<VertexBuffer> SquareVB;
		SquareVB.reset(VertexBuffer::Create(SqaureVertices, sizeof(SqaureVertices)));
		BufferLayout SquareVBlayout{
			//takes in buffer elements initializer_list
			{ ShaderDataType::Float3, "a_Position" }
		};
		SquareVB->SetLayout(SquareVBlayout);
		s_Data->QuadVertexArray->AddVertexBuffer(SquareVB);

		unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer>SquareIndexBuffer;
		SquareIndexBuffer.reset(IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
		s_Data->QuadVertexArray->SetIndexBuffer(SquareIndexBuffer);

		s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
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
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		//s_Data->FlatColorShader->SetMat4("u_Transform", glm::mat4(1.0f));
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
		(s_Data->FlatColorShader)->Bind();
		(s_Data->FlatColorShader)->SetFloat4("u_Color", color);

		//2022-9-10 handling transform matrix as position and scale
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->FlatColorShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();

		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}