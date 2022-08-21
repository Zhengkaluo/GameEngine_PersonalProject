#include "Kaluopch.h"
#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
//#include "Platform/Direct3D/Direct3dBuffer.h"

#include "Renderer.h"

namespace KaluoEngine {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		//decide which api we are using
		//which class type we instantiate
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
				KALUO_CORE_ASSERT(false, "None RenderAPi is not supported!");
				return nullptr;
		case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}
		KALUO_CORE_ASSERT(false, "UnKnown Renderer API!");
		return nullptr;
	}

	
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		//decide which api we are using
			//which class type we instantiate
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
				KALUO_CORE_ASSERT(false, "None RenderAPi is not supported!");
				return nullptr;
		case RendererAPI::API::OpenGL:
				return new OpenGLIndexBuffer(indices, size);
		}
		KALUO_CORE_ASSERT(false, "UnKnown Renderer API!");
		return nullptr;
	}

}