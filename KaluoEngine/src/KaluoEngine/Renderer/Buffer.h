#pragma once

namespace KaluoEngine {
	//just for subclass to realized this implementaion
	//and we dont need a constructor
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		//virtual void SetData()

		//define interface
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		//get data of vertices,  play as constructor
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		//define interface
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		//get data of vertices,  play as constructor
		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

}