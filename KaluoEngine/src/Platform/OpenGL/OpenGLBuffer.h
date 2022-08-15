#pragma once

#include "KaluoEngine/Renderer/Buffer.h"

namespace KaluoEngine {

	class OpenGLVertexBuffer : public VertexBuffer 
	{
	public:
		//parameter as VertexBuffer create function takes 
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;

	private:
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		//parameter as VertexBuffer create function takes 
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual uint32_t GetCount() const { return m_Count; }

		virtual void Bind() const;
		virtual void UnBind() const;

	private:
		uint32_t m_Count;

		uint32_t m_RendererID;
	};
}