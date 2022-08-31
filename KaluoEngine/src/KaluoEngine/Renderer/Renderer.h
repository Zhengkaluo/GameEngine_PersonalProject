#pragma once
#include "RendererAPI.h"
#include "OrthographicCamera.h"
#include "Shader.h"
namespace KaluoEngine{

	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& camera);//taking all scene parameter
		static void EndScene();

		//takes in information about material
		/*!
			* shared pointer of a shader
			* shared pointer of vertex array
			* a transform matrix
		*/
		static void Submit(
			const Ref<Shader>& shader,
			const Ref<VertexArray>& vertexArray,
			const glm::mat4& transformMatrix = glm::mat4(1.0f)
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