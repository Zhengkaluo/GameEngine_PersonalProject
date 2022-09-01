#include "Kaluopch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace KaluoEngine {
	Shader* Shader::Create(const std::string& FilePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: KALUO_CORE_ASSERT(false, "RendererAPI::None is not supported!");

		case RendererAPI::API::OpenGL:
			return new OpenGLShader(FilePath);
		}
		KALUO_CORE_ASSERT(false, "UnKnown Renderer API!");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& VertexSource, const std::string& FragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: KALUO_CORE_ASSERT(false, "RendererAPI::None is not supported!");

		case RendererAPI::API::OpenGL:
			return new OpenGLShader(VertexSource, FragmentSource);
		}
		KALUO_CORE_ASSERT(false, "UnKnown Renderer API!");
		return nullptr;
	}

}
