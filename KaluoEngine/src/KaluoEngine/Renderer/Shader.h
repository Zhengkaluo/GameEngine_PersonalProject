#pragma once
#include <string>

namespace KaluoEngine {
	class Shader
	{
	public:
		//from opengl wiki we know it takes two parameters of a vertex/fragment shader
		//std::string vertexSource = // Get source code for vertex shader.
		// std::string fragmentSource = // Get source code for fragment shader.
		Shader(const std::string& VertexSource, const std::string& FragmentSource);
		~Shader();

		void Bind() const;
		void UnBind() const;
	
	private:
		uint32_t m_RenderID;

	};
}