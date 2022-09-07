#include "Kaluopch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace KaluoEngine{ 
	Ref<VertexArray> VertexArray::Create() {
		//decide which api we are using
		//which class type we instantiate
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			KALUO_CORE_ASSERT(false, "None RenderAPi is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();

		}
		KALUO_CORE_ASSERT(false, "UnKnown Renderer API!");
		return nullptr;
	

	}
}