#include "Kaluopch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace KaluoEngine {
	
	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		//submit into rendercommand queue
		RenderCommand::DrawIndexed(vertexArray);
	}
}