#pragma once

#include <KaluoEngine.h>
#include "imgui/imgui.h"

class SandBox2D : public KaluoEngine::Layer
{
public:
	SandBox2D();
	virtual ~SandBox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(KaluoEngine::TimeStep timestep) override;
	virtual void OnEvent(KaluoEngine::Event& event) override;
	virtual void OnImGuiRender() override;


private:
	KaluoEngine::OrthographicCameraController m_CameraController;

	//Temp
	KaluoEngine::Ref<KaluoEngine::Shader> m_FlatColorShader;
	KaluoEngine::Ref<KaluoEngine::VertexArray> m_SquareVA;

	KaluoEngine::Ref<KaluoEngine::Texture2D> m_CheckerBoardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

};