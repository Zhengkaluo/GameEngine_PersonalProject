#include "Kaluopch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace KaluoEngine {
	
 	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		//2022-9-9 add also 2D renderer init
		Renderer2D::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transformMatrix)
	{
		//2022-8-23 bind the shader for the camera and upload camera
		shader->Bind();

		//2022-8-23 this only need to do once per scene, will be changed later
		//shader->UpLoadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		//2022-8-29 dynamic cast the upper shader into opengl shader and call the function
		std::dynamic_pointer_cast<OpenGLShader>(shader) ->UpLoadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		
		//2022-8-28 upload the transform matrix of model  
		std::dynamic_pointer_cast<OpenGLShader>(shader) -> UpLoadUniformMat4("u_Transform", transformMatrix);

		vertexArray->Bind();
		//submit into rendercommand queue
		RenderCommand::DrawIndexed(vertexArray);
	}
}