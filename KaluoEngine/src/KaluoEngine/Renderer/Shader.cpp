#include "Kaluopch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace KaluoEngine {
	Ref<Shader> Shader::Create(const std::string& FilePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: KALUO_CORE_ASSERT(false, "RendererAPI::None is not supported!");

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(FilePath);
		}
		KALUO_CORE_ASSERT(false, "UnKnown Renderer API!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& VertexSource, const std::string& FragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: KALUO_CORE_ASSERT(false, "RendererAPI::None is not supported!");

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, VertexSource, FragmentSource);
		}
		KALUO_CORE_ASSERT(false, "UnKnown Renderer API!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		//auto& name = shader->GetName();
		KALUO_CORE_ASSERT(!Exists(name), "shaders already exist!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		KALUO_CORE_ASSERT(!Exists(name), "shaders already exist!");
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		//create -> add to m_shaders -> return
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		//create -> add to m_shaders -> return
		auto shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		//
		KALUO_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "shaders not found!");
		
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}
