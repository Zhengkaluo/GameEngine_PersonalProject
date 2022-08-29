#pragma once

#include <string>

#include "KaluoEngine/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace KaluoEngine {
	class OpenGLShader : public Shader
	{
	public:
		//from opengl wiki we know it takes two parameters of a vertex/fragment shader
		//std::string vertexSource = // Get source code for vertex shader.
		// std::string fragmentSource = // Get source code for fragment shader.
		OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float values);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		
		void UploadUniformMat3(const std::string& name, const glm::mat3& values);
		void UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;

	};
}