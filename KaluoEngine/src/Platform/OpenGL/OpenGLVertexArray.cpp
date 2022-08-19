#include "Kaluopch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace KaluoEngine {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case KaluoEngine::ShaderDataType::Float: return GL_FLOAT;
			case KaluoEngine::ShaderDataType::Float2: return GL_FLOAT;
			case KaluoEngine::ShaderDataType::Float3: return GL_FLOAT;
			case KaluoEngine::ShaderDataType::Float4: return GL_FLOAT;
			case KaluoEngine::ShaderDataType::Mat3: return GL_FLOAT;
			case KaluoEngine::ShaderDataType::Mat4: return GL_FLOAT;
			case KaluoEngine::ShaderDataType::Int: return GL_INT;
			case KaluoEngine::ShaderDataType::Int2: return GL_INT;
			case KaluoEngine::ShaderDataType::Int3: return GL_INT;
			case KaluoEngine::ShaderDataType::Int4: return GL_INT;
			case KaluoEngine::ShaderDataType::Bool: return GL_BOOL;
		}
		KALUO_CORE_ASSERT(false, "Unknow shader data type to convert!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		KALUO_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Buffer Has No Layout!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			//enable the first vertex attribute
			glEnableVertexAttribArray(index);
			//define an array of generic vertex attribute data, stride meaning each column of 3*3 has 3 float data (每行有三个float)
			//2022-8-18: conversion of ShaderDataType into gl function parameters
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}