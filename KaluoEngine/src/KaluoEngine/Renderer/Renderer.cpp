#include "Kaluopch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace KaluoEngine {
	
 	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		//2022-8-23 bind the shader for the camera and upload camera
		shader->Bind();
		shader->UpLoadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		//submit into rendercommand queue
		RenderCommand::DrawIndexed(vertexArray);
	}
}