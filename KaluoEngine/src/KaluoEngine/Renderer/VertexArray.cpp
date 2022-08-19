#include "Kaluopch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace KaluoEngine{ 
	VertexArray* VertexArray::Create() {
		//decide which api we are using
		//which class type we instantiate
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			KALUO_CORE_ASSERT(false, "None RenderAPi is not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();

		}
		KALUO_CORE_ASSERT(false, "UnKnown Renderer API!");
		return nullptr;
	

	}
}