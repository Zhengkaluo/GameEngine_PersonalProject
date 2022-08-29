#include "Kaluopch.h"
#include "OpenGLShader.h"

//#include "KaluoEngine/Renderer/Renderer.h"

#include <glad/glad.h>

namespace KaluoEngine{

	OpenGLShader::OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource)
	{
		// Create an empty vertex shader handle, meaning: generate id
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = VertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		//check if compile succeed
		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			KALUO_CORE_ERROR("{0}", infoLog.data());
			KALUO_CORE_ASSERT(false, "Vertex shader compiled failed!");
			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)FragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			KALUO_CORE_ERROR("{0}", infoLog.data());
			KALUO_CORE_ASSERT(false, "Fragment shader compiled failed!");
			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			KALUO_CORE_ERROR("{0}", infoLog.data());
			KALUO_CORE_ASSERT(false, "shader program link failed!");
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(Location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float values)
	{
		GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(Location, values);

	}
	
	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(Location, values.x, values.y);
	}
	
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(Location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		//2022-8-28 upload uniform variable in float4/vec4 (meaning could be a color)
		GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(Location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{	
		//it is based on assumption that shader is already binded
		//First Get the matrix location
		GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
		//location, how many matrix, whether we should transpose, pointer to the value
		glUniformMatrix3fv(Location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		//it is based on assumption that shader is already binded
		//First Get the matrix location
		GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
		//location, how many matrix, whether we should transpose, pointer to the value
		glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}