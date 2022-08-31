#pragma once
#include "KaluoEngine/Renderer/RendererAPI.h"


namespace KaluoEngine {

	class OpenGLRendererAPI : public RendererAPI 
	{
	public:
		//2022-8-31 handling alpha blending inside init function
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	};
}