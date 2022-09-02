#include "Kaluopch.h"
#include "OpenGLShader.h"

#include <fstream>

//#include "KaluoEngine/Renderer/Renderer.h"

#include <glad/glad.h>

namespace KaluoEngine {
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		KALUO_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		//2022-9-2 extract name of file and give it to shader class
		// assets/shaders/Texture.glsl
		// so we are using the string after last slash and use it as name
		auto LastSlash = filepath.find_last_of("/\\");
		LastSlash = LastSlash == std::string::npos ? 0 : LastSlash + 1;
		auto LastDot = filepath.rfind('.');
		//determine the index if no last dot found
		auto Count = LastDot == std::string::npos ? filepath.size() - LastSlash : LastDot - LastSlash;
		m_Name = filepath.substr(LastSlash, Count);
	}
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& VertexSource, const std::string& FragmentSource)
		: m_Name(name)
	{
		//2022-9-1 moving all compile sources into compile function
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = VertexSource;
		sources[GL_FRAGMENT_SHADER] = FragmentSource;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		//at best treat it as a virtual file system
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			//file pointer into end of the file
			in.seekg(0, std::ios::end);
			//set result to the size of the file
			result.resize(in.tellg());
			//set back to the begin of the string
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			KALUO_CORE_ERROR("Could not open file '{0}'", filepath);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		//finding all the type token, and copy all the context
		while (pos != std::string::npos)
		{
			//end of line
			size_t eol = source.find_first_of("\r\n", pos);
			KALUO_CORE_ASSERT(eol != std::string::npos, "Syntax Error");
			//copy the type name
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			KALUO_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

			//from here find the next type token
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] =
				source.substr(nextLinePos,
					//untill the end of this datatype or the end of the file
					pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		GLuint program = glCreateProgram();
		//2022-9-2 change glshaderid from vectors to arrays. From stack instead of heap
		KALUO_CORE_ASSERT(shaderSources.size() <= 2, "for now only support no more than 2 size in shadersources");
		std::array<GLenum, 2> glShaderIDs;
		//glShaderIDs.reserve(shaderSources.size());
		int glShaderIDIndex = 0;
		// convert the old compile code into a loop
		for (auto& keyValue : shaderSources)
		{
			//shader type
			GLenum shaderType = keyValue.first;
			//shader source code
			const std::string& source = keyValue.second;

			// Create an empty shader handle, meaning: generate id
			GLuint Shader = glCreateShader(shaderType);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(Shader, 1, &sourceCStr, 0);

			// Compile the vertex shader
			glCompileShader(Shader);

			//check if compile succeed
			GLint isCompiled = 0;
			glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(Shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(Shader);

				// Use the infoLog as you see fit.
				KALUO_CORE_ERROR("{0}", infoLog.data());
				KALUO_CORE_ASSERT(false, "shader compiled failed!");
				// In this simple program, we'll just leave
				break;
			}
			// Attach our shaders to our program
			glAttachShader(program, Shader);

			//increase the index after the loop
			glShaderIDs[glShaderIDIndex++] = Shader;
		}
		
		m_RendererID = program;
	
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
			for(auto id : glShaderIDs)
			{
				// Don't leak shaders either.
				glDeleteShader(id);
			}
			// Use the infoLog as you see fit.
			KALUO_CORE_ERROR("{0}", infoLog.data());
			KALUO_CORE_ASSERT(false, "shader program link failed!");
			// In this simple program, we'll just leave
			return;
		}
		for (auto id : glShaderIDs)
		{
			// Always detach shaders after a successful link.
			glDetachShader(program, id);
		}
		
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