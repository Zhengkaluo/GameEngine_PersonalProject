#pragma once
#include "KaluoEngine/Renderer/Texture.h"

#include <glad/glad.h>
#include "stb_image.h"

namespace KaluoEngine {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		//2022-9-13 for you to give a pointer of block of memory and upload to gpu
		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		std::string m_Path;

		uint32_t m_Width;
		uint32_t m_Height;

		uint32_t m_RendererID;

		GLenum m_InternalFormat, m_DataFormat;
	};
}