#pragma once

#include "KaluoEngine/Renderer/Buffer.h"

namespace KaluoEngine {

	class OpenGLVertexBuffer : public VertexBuffer 
	{
	public:
		//parameter as VertexBuffer create function takes 
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;

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