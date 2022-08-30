#include "Kaluopch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace KaluoEngine {

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		/*GL_COLOR_BUFFER_BITand GL_DEPTH_BUFFER_BIT aren't functions,
		they're constants. You use them to tell glClear() which buffers you want it to clear 
		- in your example, the depth buffer and the "buffers currently enabled for color writing". 
		You can also pass GL_ACCUM_BUFFER_BIT to clear the accumulation buffer 
		and/or GL_STENCIL_BUFFER_BIT to clear the stencil buffer.*/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}



}