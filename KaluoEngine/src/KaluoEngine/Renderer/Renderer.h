#pragma once
#include "RendererAPI.h"
#include "OrthographicCamera.h"
#include "Shader.h"
namespace KaluoEngine{

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);//taking all scene parameter
		static void EndScene();

		//takes in information about material
		static void Submit(
			const std::shared_ptr<Shader>& shader,
			const std::shared_ptr<VertexArray>& vertexArray
		);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	
	private:
		struct SceneData 
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}