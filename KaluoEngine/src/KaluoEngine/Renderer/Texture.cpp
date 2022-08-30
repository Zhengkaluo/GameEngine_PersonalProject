#include "Kaluopch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace KaluoEngine {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			KALUO_CORE_ASSERT(false, "RendererAPI None is not supported!");
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}

		KALUO_CORE_ASSERT(false, "RendererAPI None is not supported!");
		return nullptr;
	}
}