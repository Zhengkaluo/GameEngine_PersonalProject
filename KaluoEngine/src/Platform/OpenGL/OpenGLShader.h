#pragma once

#include <string>

#include "KaluoEngine/Renderer/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef unsigned int GLenum;

namespace KaluoEngine {
	class OpenGLShader : public Shader
	{
	public:
		//from opengl wiki we know it takes two parameters of a vertex/fragment shader
		//std::string vertexSource = // Get source code for vertex shader.
		// std::string fragmentSource = // Get source code for fragment shader.
		OpenGLShader(const std::string& FilePath);
		OpenGLShader(const std::string& name, const std::string& VertexSource, const std::string& FragmentSource);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;


		//API set values functions
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name;  }

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float values);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		
		void UploadUniformMat3(const std::string& name, const glm::mat3& values);
		void UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		//read from glsl file
		std::string ReadFile(const std::string& filepath);
		//devide into multiple shader source codes from readfile result
		//map from shader type to each shader souce codes
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	
	private:
		uint32_t m_RendererID;

		std::string m_Name;
	};
}