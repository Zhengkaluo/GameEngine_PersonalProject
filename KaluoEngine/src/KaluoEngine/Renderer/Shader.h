#pragma once
#include <string>

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

		//2022-8-29 abstract function for specfic class implementation (later)
		//virtual void UploadUniformBuffer() = 0;

		//2022-9-1 overload create function
		static Shader* Create(const std::string& filepath);
		
		static Shader* Create(const std::string& VertexSource, const std::string& FragmentSource);

	};
}