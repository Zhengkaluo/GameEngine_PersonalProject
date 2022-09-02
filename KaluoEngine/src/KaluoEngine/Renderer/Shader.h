#pragma once

#include <string>
#include <unordered_map>

namespace KaluoEngine {
	class Shader
	{
	public:
		//from opengl wiki we know it takes two parameters of a vertex/fragment shader
		//std::string vertexSource = // Get source code for vertex shader.
		// std::string fragmentSource = // Get source code for fragment shader.
		// 2022-8-29 this class is made abstract now
		// Shader(const std::string& VertexSource, const std::string& FragmentSource);
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const std::string& GetName() const = 0;

		//2022-8-29 abstract function for specfic class implementation (later)
		//virtual void UploadUniformBuffer() = 0;

		//2022-9-1 overload create function
		static Ref<Shader> Create(const std::string& filepath);
		
		static Ref<Shader> Create(const std::string& name, const std::string& VertexSource, const std::string& FragmentSource);

	private:
		
	};

	class ShaderLibrary
	{
	public:
		//the const refference. because it only get copied when we go in to unordered_map
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);

		Ref<Shader> Load(const std::string& filePath); // assets/texture.glsl
		Ref<Shader> Load(const std::string& name, const std::string& filePath);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}