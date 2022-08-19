#pragma once
#include "KaluoEngine/Renderer/VertexArray.h"

namespace KaluoEngine {
	class OpenGLVertexArray : public VertexArray 
	{
	public:
		OpenGLVertexArray();

		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
	
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers;  };
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer;  };
		
	private:
		uint32_t m_RendererID;
		//mirroring all vertex buffers in the shared pointer list and index buffer
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};
}